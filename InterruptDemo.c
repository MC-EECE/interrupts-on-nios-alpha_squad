
#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "timerISR.h"
#include "buttonISR.h"

/*******************************************************************************
 * int main()                                                                  *
 *                                                                             *
 ******************************************************************************/

int main(void)
{ 
    /* Setup */
	alt_u32 * pCount;
	static alt_u32 count = 0;
	static alt_u32 * pKey;
	alt_u32 Key = 0x10000050;

    /* Initialize Variables */
	pCount = &count;
 	pKey = &Key;
    /* Register ISRs */


	alt_irq_register(INTERVAL_TIMER_IRQ, (void*) pCount, timerISR);
	alt_irq_register(PUSHBUTTONS_IRQ, (void*) pCount, buttonISR);
    /* Initialize Timer */
	IOWR(INTERVAL_TIMER_BASE, 2, 0xFFFF&INTERVAL_TIMER_FREQ);
	IOWR(INTERVAL_TIMER_BASE, 3, 0xFFFF&(INTERVAL_TIMER_FREQ>>16));

	IOWR(INTERVAL_TIMER_BASE,1, 0x7); //STOP=0, START=1, CONT=1, ITO=1;  0111=0x7

    /* Loop while processing interrupts */
    while( 1 ) 
    {

    }
    return 0; // should never get here
}
