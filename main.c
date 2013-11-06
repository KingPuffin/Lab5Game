#include <msp430.h>
#include "game.h"
#include "LCDdriver/LCD.h"
#include "buttons/button.h"


char timer = 0;
unsigned char player;
char string1[] = {'Y','o','u'};
char string2[] = {'W','i','n', ' ', ' ', ' ', ' ',' ', ' '};
char string3[] = {'L','o','s','e', ' ', ' ', ' ', ' ', ' '};

void init_a_timer()
{
	   TACTL &= ~(MC1|MC0);        // stop timer

	    TACTL |= TACLR;             // clear TAR

	    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	    TACTL &= ~TAIFG;            // clear interrupt flag

	    TACTL |= MC1;               // set count mode to continuous

	    TACTL |= TAIE;              // enable interrupt

	    __enable_interrupt();       // enable maskable interrupts
}

void init_butts()
{
        configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);
        P1IE |= BIT1|BIT2|BIT3|BIT4;
        P1IES |= BIT1|BIT2|BIT3|BIT4;
}



void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	init_a_timer();
	init_butts();
	initPlayer();

	__enable_interrupt();

	initSPI();
	LCDinit();
	LCDclear();
	LCDtop();
	player = initPlayer();
	printPlayer( player );
	while(1)
	{
		if( didPlayerWin( player ) )
		{
			LCDclear();
			writeString( string1, 3 );
			LCDbottom();
			writeString( string2, 9 );
			__disable_interrupt();
			while(1)
			{

			}
		}
		if( timer == 4 )
		{
			LCDclear();
			writeString( string1, 3 );
			LCDbottom();
			writeString( string3, 9 );
			__disable_interrupt();
			while(1)
			{

			}
		}
	}
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A_ISR()
{
	TACTL &= ~TAIFG;

	timer++;

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{
	if( P1IFG & BIT1 )
	{
		if( isP1ButtonPressed( BIT1 ) )
		{
			clearPlayer( player );
			player = movePlayer( player, RIGHT );
			printPlayer( player );
			TAR = 0;
			timer = 0;
			debounce();
		}

		P1IFG &= ~BIT1;
	}

	if( P1IFG & BIT2 )
	{
		if( isP1ButtonPressed( BIT2 ) )
		{
			clearPlayer( player );
			player = movePlayer( player, LEFT );
			printPlayer( player );
			TAR = 0;
			timer = 0;
			waitForP1ButtonRelease( BIT2 );
			debounce();
		}
		P1IFG &= ~BIT2;
	}

	if( P1IFG & BIT3 )
	{
		if( isP1ButtonPressed( BIT3 ) )
		{
			clearPlayer( player );
			player = movePlayer( player , UP );
			printPlayer( player );
			TAR = 0;
			timer = 0;
			waitForP1ButtonRelease( BIT3 );
			debounce();
		}
		P1IFG &= ~BIT3;
	}

	if( P1IFG & BIT4 )
	{
		if( isP1ButtonPressed( BIT4 ) )
		{
			clearPlayer( player );
			player = movePlayer( player, DOWN );
			printPlayer( player );
			TAR = 0;
			timer = 0;
			waitForP1ButtonRelease( BIT4 );
			debounce();
		}
		P1IFG &= ~BIT4;
	}

}
