#!/usr/bin/env python3
"""Compile the actual G071 handlers with W1C EXTI/register mocks; no MCU SDK needed."""
from pathlib import Path
import os
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def function(path, name):
    text = (ROOT / path).read_text()
    text = re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)
    start = text.index('void ' + name + '(')
    opening = text.index('{', start)
    # Top-level closing brace; conditional compilation duplicates inner braces.
    closing = re.search(r'^}', text[opening:], flags=re.M)
    assert closing is not None
    return text[start:opening + closing.end()]


MOCKS = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#define LL_EXTI_LINE_17 (1u << 17)
#define LL_EXTI_LINE_18 (1u << 18)
struct exti_regs { uint32_t IMR1, RPR1, FPR1; } exti;
struct timer_regs { uint32_t CNT; } timer;
#define EXTI (&exti)
#define INTERVAL_TIMER (&timer)
#define INTERVAL_TIMER_COUNT timer.CNT
#define SET_INTERVAL_TIMER_COUNT(v) (timer.CNT = (v))
#define SET_AND_ENABLE_COM_INT(v) (scheduled++, scheduled_wait = (v))
#define __disable_irq() ((void)0)
#define __enable_irq() ((void)0)
#define LL_EXTI_ClearRisingFlag_0_31(v) (exti.RPR1 &= ~(v))
#define LL_EXTI_ClearFallingFlag_0_31(v) (exti.FPR1 &= ~(v))
#define LL_EXTI_IsActiveRisingFlag_0_31(v) ((exti.RPR1 & (v)) != 0)
#define LL_EXTI_IsActiveFallingFlag_0_31(v) ((exti.FPR1 & (v)) != 0)
uint32_t current_EXTI_LINE, average_interval, lastzctime, thiszctime;
uint32_t scheduled, scheduled_wait, waitTime;
int filter_level, rising, comp_level;
uint8_t getCompOutputLevel(void) { return comp_level; }
void maskPhaseInterrupts(void) {
    exti.IMR1 &= ~(LL_EXTI_LINE_17 | LL_EXTI_LINE_18);
    exti.RPR1 &= ~(LL_EXTI_LINE_17 | LL_EXTI_LINE_18);
    exti.FPR1 &= ~(LL_EXTI_LINE_17 | LL_EXTI_LINE_18);
}
static void reset(uint32_t line, int direction, uint32_t time) {
    exti = (struct exti_regs){.IMR1 = line};
    current_EXTI_LINE = line;
    average_interval = 1250; /* 62.5 us at 20 ticks/us */
    timer.CNT = time;
    rising = direction;
    comp_level = !direction;
    filter_level = 2;
    scheduled = scheduled_wait = 0;
    lastzctime = 1200;
    thiszctime = 1250;
    waitTime = 312;
}
static void edge(void) {
    if (rising) exti.FPR1 |= current_EXTI_LINE;
    else exti.RPR1 |= current_EXTI_LINE;
}
'''

TESTS = r'''
int main(void) {
    const uint32_t lines[] = {LL_EXTI_LINE_17, LL_EXTI_LINE_18};
    for (unsigned line = 0; line < 2; ++line) {
        for (int direction = 0; direction < 2; ++direction) {
            reset(lines[line], direction, 1250);
            edge(); ADC1_COMP_IRQHandler();
            assert(scheduled == 1 && scheduled_wait == 313);
            assert(lastzctime == 1250 && thiszctime == 1250 && timer.CNT == 0);
            ADC1_COMP_IRQHandler(); assert(scheduled == 1);

            reset(lines[line], direction, 1250);
            comp_level = rising; edge(); ADC1_COMP_IRQHandler();
            assert(scheduled == 0 && timer.CNT == 1250); /* level filter */

            for (uint32_t t = 624; t <= 626; ++t) {
                reset(lines[line], direction, t);
                edge(); ADC1_COMP_IRQHandler();
                assert(scheduled == (t > 625));
#if AM32_G071_STRICT_ZC_IRQ
                assert((exti.RPR1 | exti.FPR1) == 0);
                if (t <= 625) {
                    assert(timer.CNT == t && lastzctime == 1200 && thiszctime == 1250);
                    timer.CNT = 1250;
                    ADC1_COMP_IRQHandler(); assert(scheduled == 0); /* no replay */
                    edge(); ADC1_COMP_IRQHandler(); assert(scheduled == 1);
                }
#else
                if (t <= 625) {
                    assert((exti.RPR1 | exti.FPR1) != 0); /* legacy latch */
                    timer.CNT = 1250;
                    ADC1_COMP_IRQHandler(); assert(scheduled == 1);
                }
#endif
            }
#if AM32_G071_STRICT_ZC_IRQ
            reset(lines[line], direction, 1250);
            edge(); exti.IMR1 = 0; ADC1_COMP_IRQHandler();
            assert(scheduled == 0 && (exti.RPR1 | exti.FPR1) == 0);

            reset(lines[line], direction, 1250);
            if (rising) exti.RPR1 = current_EXTI_LINE;
            else exti.FPR1 = current_EXTI_LINE;
            ADC1_COMP_IRQHandler(); assert(scheduled == 0); /* wrong polarity */

            reset(lines[line], direction, 1250);
            exti.FPR1 = exti.RPR1 = lines[1 - line];
            ADC1_COMP_IRQHandler(); assert(scheduled == 0); /* inactive COMP */

            reset(lines[line], direction, 1250);
            exti.FPR1 = exti.RPR1 = lines[1 - line]; edge();
            ADC1_COMP_IRQHandler(); assert(scheduled == 1); /* active wins */

            reset(lines[line], direction, 1250);
            exti.IMR1 = 0;
            exti.FPR1 = exti.RPR1 = LL_EXTI_LINE_17 | LL_EXTI_LINE_18 | 4;
            enableCompInterrupts();
            assert(exti.IMR1 == lines[line]);
            assert(exti.FPR1 == 4 && exti.RPR1 == 4); /* other EXTI preserved */
            ADC1_COMP_IRQHandler(); assert(scheduled == 0);
            edge(); ADC1_COMP_IRQHandler(); assert(scheduled == 1);
#endif
        }
    }
    puts("G071 ZC IRQ tests passed");
    return 0;
}
'''


def main():
    source = MOCKS + '\n' + '\n'.join([
        function('Src/main.c', 'interruptRoutine'),
        function('Mcu/g071/Src/comparator.c', 'enableCompInterrupts'),
        function('Mcu/g071/Src/stm32g0xx_it.c', 'ADC1_COMP_IRQHandler'),
    ]) + '\n' + TESTS
    with tempfile.TemporaryDirectory() as temp:
        path = Path(temp)
        (path / 'test.c').write_text(source)
        for enabled in (0, 1):
            subprocess.run([os.environ.get('CC', 'cc'), '-std=c99', '-Wall',
                            '-Wextra', '-Werror', '-fsanitize=undefined',
                            f'-DAM32_G071_STRICT_ZC_IRQ={enabled}',
                            str(path / 'test.c'), '-o', str(path / 'test')], check=True)
            subprocess.run([str(path / 'test')], check=True)
            print(f'AM32_G071_STRICT_ZC_IRQ={enabled}: PASS', flush=True)


if __name__ == '__main__':
    main()
