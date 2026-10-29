/*
 * comparator.h
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#ifndef COMPARATOR_H_
#define COMPARATOR_H_

/* Experimental: discard stale/early EXTI edges instead of retaining them.
 * Enable only for instrumented bench validation; see doc/development/G071-ZC.md.
 */
#ifndef AM32_G071_STRICT_ZC_IRQ
#define AM32_G071_STRICT_ZC_IRQ 0
#endif
#if AM32_G071_STRICT_ZC_IRQ != 0 && AM32_G071_STRICT_ZC_IRQ != 1
#error "AM32_G071_STRICT_ZC_IRQ must be 0 or 1"
#endif

#endif /* COMPARATOR_H_ */

#include "main.h"

void maskPhaseInterrupts();
void changeCompInput();
void enableCompInterrupts();
uint8_t getCompOutputLevel();
extern volatile char rising;
extern char step;

extern uint32_t current_EXTI_LINE;

