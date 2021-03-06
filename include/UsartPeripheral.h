#pragma once
#include "cmsis_device.h"
#include "Common.h"
#include "Usart.h"
#include "Rcc.h"
#include "ClockControl.h"
#include "Traits.h"
#include "UsartPinInitialiser.h"

namespace youth_zhao{

template<class TPinPackage, PeripheralName TPeripheralName>
class UsartPeripheral : public Usart {

public:
	struct Parameters {
		uint32_t usart_baudRate;              ///< Your choice
		uint16_t usart_wordLength;            ///< USART_Word_Length
		uint16_t usart_parity;                ///< USART_Parity
		uint16_t usart_stopBits;              ///< USART_Stop_Bits
		uint16_t usart_flowControl;           ///< USART_HardwareFlowControl
		uint16_t usart_mode;                  ///< USART_Mode
		bool usart_synchronous;               ///< true if there's a USART clock signal

	Parameters(uint32_t baudRate=9600) {
		usart_baudRate=baudRate;
		usart_wordLength=USART_WordLength_8b;
		usart_parity=USART_Parity_No;
		usart_stopBits=USART_StopBits_1;
		usart_flowControl=USART_HardwareFlowControl_None;
		usart_mode=USART_Mode_Rx | USART_Mode_Tx;
		usart_synchronous=false;
  }
};

public:
  UsartPeripheral(const Parameters& params);
  ~UsartPeripheral();
};



template<class TPinPackage,PeripheralName TPeripheralName>
inline UsartPeripheral<TPinPackage,TPeripheralName>::UsartPeripheral(const Parameters& params)
: Usart((USART_TypeDef *)PeripheralTraits<TPeripheralName>::PERIPHERAL_BASE) {

	USART_InitTypeDef init;

	// clocks on first before any features get initialised

	ClockControl<TPeripheralName>::On();

	// and next the GPIO pins, also before any features get initialised

	UsartPinInitialiser<TPinPackage,TPeripheralName>::initialise(
		params.usart_mode,
		params.usart_baudRate,
		params.usart_synchronous);

	// initialise the peripheral

	USART_StructInit(&init);

	init.USART_BaudRate=params.usart_baudRate;
	init.USART_WordLength=params.usart_wordLength;
	init.USART_Parity=params.usart_parity;
	init.USART_StopBits=params.usart_stopBits;
	init.USART_HardwareFlowControl=params.usart_flowControl;
	init.USART_Mode=params.usart_mode;

	// initialise

	USART_Init((USART_TypeDef *)PeripheralTraits<TPeripheralName>::PERIPHERAL_BASE,&init);

	// enable

	enablePeripheral();
}


  /**
   * Destructor, disable peripheral and disable clocks
   */

  template<class TPinPackage,PeripheralName TPeripheralName>
  inline UsartPeripheral<TPinPackage,TPeripheralName>::~UsartPeripheral() {

    // disable the peripheral

    disablePeripheral();

    // clocks off

    ClockControl<TPeripheralName>::Off();
  }


}

