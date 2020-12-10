#pragma once
#include "cmsis_device.h"
namespace youth_zhao{

class Timer
{
public:
	typedef uint32_t ticks_t;
	static constexpr ticks_t FREQUENCY_HZ = 1000u;

private:
	static volatile ticks_t ms_delayCount;

public:
	Timer() = default;
	inline static void start(void){
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
		SysTick_Config(SystemCoreClock / FREQUENCY_HZ);
	}

	inline static void tick(void);
	static void sleep(ticks_t ticks);
};


class AlineTimer{
public:
	volatile static uint8_t fac_us;
	volatile static uint16_t fac_ms;

	AlineTimer() {
	}
	static void delay_init(void);
	static void delay_us(u32 nus);
	static void delay_ms(u16 nms);
protected:
private:

};


class MillisecondTimer {

  public:
    volatile static uint32_t _counter;

  public:
    static void initialise();
    static void __attribute__ ((weak)) delay(uint32_t millis_);
    static uint32_t millis();
    static void reset();
    static bool hasTimedOut(uint32_t start,uint32_t timeout);
    static uint32_t difference(uint32_t start);
};


/**
 * Get the current value of the systick counter.
 * @return The current value of the counter.
 */
inline uint32_t MillisecondTimer::millis() {
  return _counter;
}

/**
 * Reset the counter to zero
 */
inline void MillisecondTimer::reset() {
  _counter=0;
}

/**
 * Check if a timeout has been exceeded. This is designed to cope with wrap around
 * @return true if the timeout has expired
 */
inline bool MillisecondTimer::hasTimedOut(uint32_t start,uint32_t timeout) {
  return difference(start)>timeout;
}

/**
 * Return the difference between a starting time and now, taking into account
 * wrap around
 * @param start when we started timing
 * @return The difference
 */

inline uint32_t MillisecondTimer::difference(uint32_t start) {

  uint32_t now=millis();

  if(now>=start)
    return now-start;
  else
    return now+(UINT32_MAX-start+1);
}

}







