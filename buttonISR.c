/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */

#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
	static timerlol= 0x10002000;
	static Key1 = 2;
	static Key2 = 4;
	static Key3 = 8;
	alt_u8 buttons= IORD( PUSHBUTTONS_BASE , 3);
	alt_u32* pCount = (alt_u32*)context;
	alt_u8 timer_setting
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */

    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */

    /* Reset the PUSHBUTTONS's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(context, 0);

    /* Act upon the interrupt */
    switch (buttons){
    	case Key1:
    		if (timer_setting & 0x8){
    			timer_setting = 0x7;
    			LCD_cursor(0,0);
    			LCD_text("Dis Running, YO...");
    		}
    		else{ timer_setting = 0xE;
    			LCD_cursor(0,0);
    			LCD_text("Dis Now Paused, YO...");
    		}
    	//case Key2:

    }
    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(context);
}
