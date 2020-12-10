#pragma once

namespace youth_zhao{

class StreamBase {

protected:
      virtual ~StreamBase() {}

public:

      /**
       * Error codes
       */

      enum {
        /// End of stream has been reached
        E_END_OF_STREAM=-1,

        /// An error occurred while reading from the stream
        E_STREAM_ERROR=-2,

        /// The operation is not supported
        E_OPERATION_NOT_SUPPORTED=-3
      };

public:

      /**
       * Close the stream. If the stream does not support the operation
       * then it returns true.
       * @return false if it fails.
       */

      virtual bool close()=0;
  };

}

