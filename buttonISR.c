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
#include "HexDisplay.h"
#include "alt_types.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
	// declarations and defs

	#define Key0 1
	#define Key1 2
	#define Key2 4
	#define Key3 8

	alt_u8 timer_toggle;

    /* Cast context it is important that this be declared
     * volatile to avoid unwanted compiler optimization.
     */
	alt_u32* pCount = (alt_u32*)context;

    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */
	alt_u8 buttons= IORD(PUSHBUTTONS_BASE , 3);

    /* Reset the PUSHBUTTONS's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0);

    /* Act upon the interrupt */
    switch (buttons){
    	case Key0:
    	break;
    	case Key1:
    		timer_toggle = IORD(INTERVAL_TIMER_BASE,1);
    		if ((0x8&timer_toggle)!=0){
    			timer_toggle = 0x7;
    			LCD_cursor(0,0);
    			LCD_text("Dis Running, YO...                   ");
    		}
    		else{
    			timer_toggle = 0xB;
    			LCD_cursor(0,0);
    			LCD_text("Dis Paused, YO...                    ");
    		}
    		IOWR(INTERVAL_TIMER_BASE, 1, timer_toggle);
    		break;
    	case Key2:
    		*pCount = 0;
    		HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);
    		LCD_cursor(0,0);
    		LCD_text("Key 2 pressed...YO...                    ");
    		break;
    	case Key3:
    		change_display_type();
    		HexDisplay((alt_u32*)HEX3_HEX0_BASE, *pCount);
    		LCD_cursor(0,0);
    		LCD_text("Key 3 pressed... YO...                    ");
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

