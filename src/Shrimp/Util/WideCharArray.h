#ifndef SHRIMP_UTIL_WIDECHARS
#define SHRIMP_UTIL_WIDECHARS

#include <string>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    class WideCharArray : private Uncopyable {
    public:
      WideCharArray(const std::string& str);
      ~WideCharArray() throw();
      wchar_t* GetPtr();
    private:
      wchar_t* wchars;
    };

  }
}

#endif
