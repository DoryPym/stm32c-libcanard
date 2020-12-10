#pragma once
#include "cmsis_device.h"
#include "ClockControl.h"

namespace youth_zhao{

  template<>
  struct ClockControl<PERIPHERAL_USART1> {

    static void On() {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,ENABLE);
    }

    static void Off() {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,DISABLE);
    }
  };

  /**
   * USART2
   */

  template<>
  struct ClockControl<PERIPHERAL_USART2> {

    static void On() {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    }

    static void Off() {
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,DISABLE);
    }
  };

}
