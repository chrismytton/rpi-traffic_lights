// GPIO demo based on the 
//
// Gertboard test suite
//
// These program walks the LEDs
//
//
// This file is part of gertboard test suite.
//
//
// Copyright (C) Gert Jan van Loo & Myra VanInwegen 2012
// No rights reserved
// You may treat this program as if it was in the public domain
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//
// Try to strike a balance between keep code simple for
// novice programmers but still have reasonable quality code
//

#include "gb_common.h"
// North side yellow has changed to pin 27 for new Rev 2 board.
// 6-12-12 www.skpang.co.uk

// I/O access
volatile unsigned *gpio;

#define RED_NORTH (1<<17)		//North set of traffic light
#define YEL_NORTH (1<<27)
#define GRN_NORTH (1<<22)

#define RED_EAST (1<<25)		//East set of traffic light
#define YEL_EAST (1<<8)
#define GRN_EAST (1<<7)

#define ALL_LEDS  (RED_NORTH|YEL_NORTH|GRN_NORTH|RED_EAST|YEL_EAST|GRN_EAST)

// LEDs test GPIO mapping:
//         Function            Mode
// GPIO0=  unused
// GPIO1=  unused
// GPIO4=  unused
// GPIO7=  LED                 Output
// GPIO8=  LED                 Output
// GPIO9=  LED                 Output
// GPIO10= LED                 Output
// GPIO11= LED                 Output
// GPIO14= unused (preset to be UART)
// GPIO15= unused (preset to be UART)
// GPIO17= LED                 Output
// GPIO18= LED                 Output
// GPIO21= LED                 Output
// GPIO22= LED                 Output
// GPIO23= LED                 Output
// GPIO24= LED                 Output
// GPIO25= LED                 Output

void setup_gpio(void)
{
  INP_GPIO(7);  OUT_GPIO(7);
  INP_GPIO(8);  OUT_GPIO(8);
  INP_GPIO(9);  OUT_GPIO(9);
  INP_GPIO(10);  OUT_GPIO(10);
  INP_GPIO(11);  OUT_GPIO(11);
  // 14 and 15 are already set to UART mode
  // by Linux. Best if we don't touch them
  INP_GPIO(17);  OUT_GPIO(17);
  INP_GPIO(18);  OUT_GPIO(18);
  INP_GPIO(21);  OUT_GPIO(21);
  INP_GPIO(22);  OUT_GPIO(22);
  INP_GPIO(23);  OUT_GPIO(23);
  INP_GPIO(24);  OUT_GPIO(24);
  INP_GPIO(25);  OUT_GPIO(25);
} // setup_gpio


int main(void)
{ 

  printf ("Traffic light demo\n");

  // Map the I/O sections
  setup_io();

  // Set 12 GPIO pins to output mode
  setup_gpio();

  GPIO_CLR0 = ALL_LEDS;		//Turn all LEDs off

  int i = 1;

  while(i < 4)	//Loop forever
  {
    printf("Traffic lights loop %d\n", i);

	GPIO_SET0 = RED_NORTH | GRN_EAST;	// Turn on North red. Turn on East green
	long_wait(80);						// Wait a bit
	GPIO_CLR0 = ALL_LEDS;				// Turn led off
	
	GPIO_SET0 = RED_NORTH | YEL_EAST;	// Turn on North red. Turn on East yellow 
	long_wait(20);						// Wait a short bit
	GPIO_CLR0 = ALL_LEDS;				// Turn led off
	
	GPIO_SET0 = RED_NORTH | RED_EAST;
	long_wait(20);
	GPIO_CLR0 = ALL_LEDS;

	GPIO_SET0 = YEL_NORTH | RED_EAST;
	long_wait(20);
	GPIO_CLR0 = ALL_LEDS;

	GPIO_SET0 = GRN_NORTH | RED_EAST;
	long_wait(80);
	GPIO_CLR0 = ALL_LEDS;	

	GPIO_SET0 = YEL_NORTH | RED_EAST;
	long_wait(20);
	GPIO_CLR0 = ALL_LEDS;

	GPIO_SET0 = RED_NORTH | RED_EAST;
	long_wait(20);
	GPIO_CLR0 = ALL_LEDS;	
	
	GPIO_SET0 = RED_NORTH | YEL_EAST;
	long_wait(20);
	GPIO_CLR0 = ALL_LEDS;
	
	
  i++;
  } 

  GPIO_CLR0 = ALL_LEDS;	//Turn all LEDs off
  restore_io();
} // main



