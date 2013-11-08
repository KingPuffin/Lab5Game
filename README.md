# A Simple Game
Library for working playing a simple game on the MSP430 utilizing the LCD screen on the black box.
Example code included in main.c with TimerA clock and Button interrupts

## General Notes
Assumes buttons are active low.  Configures with internal pull-up resistor if button open state is floating.
Implements the LCD library and buttons library.

## Functions

- `unsigned char initPlayer()`
    - Initialize player to 0x80, the top left of the screen

- `void printPlayer(unsigned char player)`
    - Prints the player to the current location
    - Writes an * to the LCD screen at the location represented by the char player
    
- `void clearPlayer(unsigned char player)`
    - Writes a ' ' at the location player
    
- `unsigned char movePlayer(unsigned char player, unsigned char direction)`
    - The button pushed determines which direction is passed
    - The char player will then be incremented or decrimented for left/right
    - The first nibble will be set or cleared with a mask to switch between lines for up/down
            
- `char didPlayerWin(unsigned char player)`
    - Checks to see if the player is in 0xC0
    - If not there will return a 0, if there returns 1
    
## License
Anyone is free to use and modify this for any purpose, provided they pay $15,000.
