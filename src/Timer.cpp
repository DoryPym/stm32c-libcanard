#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"

namespace youth_zhao{

#if defined(USE_HAL_DRIVER)
extern "C" void HAL_IncTick(void);
#endif


volatile Timer::ticks_t Timer::ms_delayCount;
volatile uint32_t MillisecondTimer::_counter;
volatile uint8_t AlineTimer::fac_us;
volatile uint16_t AlineTimer::fac_ms;


void Timer::sleep(ticks_t ticks){
	ms_delayCount = ticks;
	while (ms_delayCount != 0u);
}

inline void Timer::tick(void){
	if (ms_delayCount != 0u)
	{
		--ms_delayCount;
	}
}

void AlineTimer::delay_init() {
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SystemCoreClock/8000000;
	fac_ms=(u16)fac_us*1000;
}
void AlineTimer::delay_us(u32 nus) {
	u32 temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}
void AlineTimer::delay_ms(u16 nms) {
	u32 temp;
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}
/**
 * Initialise SysTick to tick at 1ms by initialising it with SystemCoreClock/1000.
 */
void MillisecondTimer::initialise() {
	_counter=0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);
}
/**
 * Delay for given time. Waits for the current value of the systick counter to reach a target.
 * @param millis The amount of time to wait.
 */

void MillisecondTimer::delay(uint32_t millis) {

	uint32_t target;

	target=_counter+millis;
	while(_counter<target);
}


extern "C" {
	void __attribute__ ((weak,interrupt("IRQ"))) SysTick_Handler(void) {
		MillisecondTimer::_counter++;
	}
}
}

// ----------------------------------------------------------------------------
