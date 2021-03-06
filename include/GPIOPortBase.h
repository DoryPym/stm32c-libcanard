#pragma once
#include "cmsis_device.h"
#include <cstring>

namespace youth_zhao {


  class Gpio;

  /**
   * Base class for the GpioPort template class
   */

  class GpioPortBase {

    public:
      Gpio *_pinHandlers[16];
      GPIO_TypeDef *_peripheralAddress;
      uint8_t _low;

    public:
      GpioPortBase(GPIO_TypeDef *peripheralAddress);

      void setPinHandler(uint8_t index,Gpio *pinHandler);
      GPIO_TypeDef *getPeripheralAddress() const;
  };


  /**
   * Constructor
   * @param peripheralAddress
   */

  inline GpioPortBase::GpioPortBase(GPIO_TypeDef *peripheralAddress)
    : _peripheralAddress(peripheralAddress) {
    memset(_pinHandlers,'\0',sizeof(_pinHandlers));
    _low=15;
  }


  /**
   * Set the pin handler for the pin at a given position
   * @param index The position (0..15)
   * @param pinHandler The handler for that position
   */

  inline void GpioPortBase::setPinHandler(uint8_t index,Gpio *pinHandler) {

    _pinHandlers[index]=pinHandler;

    if(index<_low)
      _low=index;
  }


  /**
   * Cast to the GPIO peripheral address
   */

  inline GPIO_TypeDef *GpioPortBase::getPeripheralAddress() const {
    return _peripheralAddress;
  }
}




