#include <msp430g2553.h>
#include "game.h"
#include "LCDdriver/LCD.h"




unsigned char initPlayer()
{
	return 0x80;
}

void printPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
	if( direction == DOWN )
	{
		player |= ROW_MASK;
	}
	else if( direction == UP )
	{
		player &= ~ROW_MASK;
	}
	else if( direction == LEFT )
	{
		if( (player & 0x0f) > 0 )
		{
			player --;
		}
	}
	else
	{
		if( (player & 0x0f) < 7 )
		{
			player ++;
		}
	}

	return player;
}

char didPlayerWin(unsigned char player)
{
	return player == 0xC7;
}
