#pragma once
#include "Common.h"


namespace youth_zhao {


  /**
   * This is the dummy implementation for the F1.
   */

template<PeripheralName TPeripheralName,uint32_t TPort,uint16_t TPin>
struct GpioAlternateFunctionMapper {
    enum {
      GPIO_AF = 0       ///< never used
    };
  };
}

