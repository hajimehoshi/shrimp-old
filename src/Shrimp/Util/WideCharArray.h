#ifndef SHRIMP_UTIL_WIDECHARS
#define SHRIMP_UTIL_WIDECHARS

#include <string>
#include <windows.h>
#include <tchar.h>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    class WideCharArray : private Uncopyable {
    public:
      WideCharArray(const std::string& str);
      ~WideCharArray();
      WCHAR* GetPtr();
    private:
      WCHAR* wchars;
    };

  }
}

#endif
