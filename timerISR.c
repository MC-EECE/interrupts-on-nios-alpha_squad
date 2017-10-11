/*
 * timerISR.c
 *
 *  Created on: 10/11/2017
 *      Author: David Thomas Jude  Chung Oakes
 */
#include "system.h"
#include "alt_types.h"
#include "HexDisplay.h"
#include "seven_seg_bcd.h"
#include "seven_seg_hex.h"
#include "buttonISR.h"
#include "io.h"

/*****************************************************************************
 * Interval timer interrupt service routine
 *
 *
******************************************************************************/
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void timerISR(void* context)
#else
void timerISR(void * context, alt_u32 id)
#endif
{
	/* Cast context. It is important that this be declared
	 * volatile to avoid unwanted compiler optimization.
	 */

	alt_u32* pCount =  (alt_u32*) context;
	/* clear the interrupt */

    /* counter intial @ 0 pass in as context variable
     * find way to increment by 1 then pass back out via *count_ptr
     */
	IOWR(INTERVAL_TIMER_BASE, 0, 1);
	/* Act upon the interrupt */
	*pCount = *pCount +1;
	/* Display count value 
	 * (Is this the best place to do this? 
	 * Why or why not?) 
	 */
	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);

	return;
}



