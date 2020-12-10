#pragma once
#include "cmsis_device.h"
#include "Common.h"
#include "UsartPeripheral.h"

namespace youth_zhao{

template<class TPinPackage,class... Features>
struct Usart1_Custom : UsartPeripheral<TPinPackage,PERIPHERAL_USART1>,Features... {

Usart1_Custom(const typename UsartPeripheral<TPinPackage,PERIPHERAL_USART1>::Parameters& params)
  : UsartPeripheral<TPinPackage,PERIPHERAL_USART1>(params),
	Features(static_cast<Usart&>(*this))... {
}
};

struct Usart1DefaultPinPackage {
    enum {
      Port_CK=GPIOA_BASE,
      Port_TX=GPIOA_BASE,
      Port_RX=GPIOA_BASE,
      Port_CTS=GPIOA_BASE,
      Port_RTS=GPIOA_BASE,

      Pin_CK=GPIO_Pin_8,
      Pin_TX=GPIO_Pin_9,
      Pin_RX=GPIO_Pin_10,
      Pin_CTS=GPIO_Pin_11,
      Pin_RTS=GPIO_Pin_12
    };
};
template<class... Features>
struct Usart1 : UsartPeripheral<Usart1DefaultPinPackage,PERIPHERAL_USART1>,
                  Features... {
    Usart1(const Parameters& params)
      : UsartPeripheral<Usart1DefaultPinPackage,PERIPHERAL_USART1>(params),
        Features(static_cast<Usart&>(*this))... {
    }
  };

struct Usart1Remap1PinPackage {
    enum {
      Port_TX=GPIOB_BASE,
      Port_RX=GPIOB_BASE,
      Port_RTS=GPIOA_BASE,
      Port_CTS=GPIOA_BASE,
      Port_CK=GPIOA_BASE,

      Pin_TX=GPIO_Pin_6,
      Pin_RX=GPIO_Pin_7,
      Pin_RTS=GPIO_Pin_12,
      Pin_CTS=GPIO_Pin_11,
      Pin_CK=GPIO_Pin_8
    };
  };

template<class... Features>
struct Usart1_Remap1 : UsartPeripheral<Usart1Remap1PinPackage,PERIPHERAL_USART1>,
                         Features... {

    Usart1_Remap1(const Parameters& params)
      : UsartPeripheral<Usart1Remap1PinPackage,PERIPHERAL_USART1>(params),
        Features(static_cast<Usart&>(*this))... {

      GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
    }
  };

}








