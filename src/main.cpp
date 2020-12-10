#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
#include "UsartPollingOutputStream.h"
#include "Usart1.h"

using namespace youth_zhao;

  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;


// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	AlineTimer::delay_init();
	//Usart<> uart1;
	Usart1<> usart(57600);

	UsartPollingOutputStream outputstream(usart);

	BlinkLed blinkLed;
	blinkLed.powerUp();

	while (1)
	{
		blinkLed.turnOn();
		AlineTimer::delay_ms(100);
		blinkLed.turnOff();
		AlineTimer::delay_ms(100);
	}
	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
