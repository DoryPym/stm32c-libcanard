#pragma once
#include "cmsis_device.h"
#include "OutputStream.h"
#include "Usart.h"

namespace youth_zhao{

class UsartPollingOutputStream : public OutputStream {

protected:
      Usart& _usart;

public:
      UsartPollingOutputStream(Usart& usart);
      virtual ~UsartPollingOutputStream() {}

      // overrides from OutputStream

      virtual bool write(uint8_t c) override;
      virtual bool write(const void *buffer,uint32_t size) override;

      /**
       * Always true.
       * @return always true
       */

      virtual bool flush() override {
        return true;
      }

      /**
       * Always true.
       * @return always true
       */

      virtual bool close() override {
        return true;
      }
  };

}



