#pragma once
#include "stm32f10x.h"

namespace youth_zhao{

// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
#define BLINK_PORT_NUMBER               (0)
#define BLINK_PIN_NUMBER                (3)
#define BLINK_ACTIVE_LOW                (0)

#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_APB2Periph_GPIOA << (_N))
// ----------------------------------------------------------------------------

class BlinkLed
{
public:
	BlinkLed() = default;
	void powerUp();

	inline void __attribute__((always_inline))turnOn()
	{
#if (BLINK_ACTIVE_LOW)
    GPIO_ResetBits(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER));
#else
    GPIO_SetBits(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER));
#endif
  }

  inline void __attribute__((always_inline))turnOff()
  {
#if (BLINK_ACTIVE_LOW)
    GPIO_SetBits(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER));
#else
    GPIO_ResetBits(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER));
#endif
  }
};

}
