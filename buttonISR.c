/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */
#include "system.h"
#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "sys\alt_irq.h"
#include "lcd.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{

	/*static int Key1 = 2;
	static int Key2 = 4;
	static int Key3 = 8;*/


	alt_u8 timer_setting;
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */
	alt_u32* pCount = (alt_u32*)context;
    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */
	alt_u8 buttons= IORD(PUSHBUTTONS_BASE , 3);
    /* Reset the PUSHBUTTONS's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0);

    /* Act upon the interrupt */
    switch(buttons){
    	case 2:
    		timer_setting = IORD(INTERVAL_TIMER_BASE,1);
    		if (timer_setting & 0x8){
    			timer_setting = 0x7;
    			LCD_cursor(0,0);
    			LCD_text("Dis Running, YO...");
    		}
    		else{
    			timer_setting = 0xB;
    			LCD_cursor(0,0);
    			LCD_text("Dis Now Paused, YO...");
    		}
    		IOWR(INTERVAL_TIMER_BASE, 1, timer_setting);
    		break;

    	case 4:	//case Key2:

    		*pCount = 0;
    		HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);
    		LCD_cursor(0,1);
    		LCD_text("Key 2 was just pressed...YO...");
    		break;


    	default:
    	break;
    	}

IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
    }
    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */

