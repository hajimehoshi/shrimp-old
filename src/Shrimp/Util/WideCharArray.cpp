#include "Shrimp/Util/WideCharArray.h"

namespace Shrimp {
  namespace Util {

    WideCharArray::WideCharArray(const std::string& str)
      : wchars(0) {
      int wTextLength = ::MultiByteToWideChar(CP_UTF8,
                                              MB_ERR_INVALID_CHARS,
                                              str.c_str(),
                                              str.length(),
                                              0,
                                              0);
      if (0 < wTextLength) {
        this->wchars = new WCHAR[wTextLength + 1];
        ::MultiByteToWideChar(CP_UTF8,
                              MB_ERR_INVALID_CHARS,
                              str.c_str(),
                              str.length(),
                              this->wchars,
                              wTextLength);
        this->wchars[wTextLength] = 0;
      } else {
        this->wchars = new WCHAR[1];
        this->wchars[0] = 0;
      }
    }

    WideCharArray::~WideCharArray() {
      delete[] this->wchars;
    }

    WCHAR* WideCharArray::GetPtr() {
      return this->wchars;
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Util {

    TEST(WideCharArray, WideCharArray) {
      ASSERT_EQ(std::wstring(L"foo"),
                std::wstring(WideCharArray("foo").GetPtr()));
      ASSERT_EQ(std::wstring(L"日本語"),
                std::wstring(WideCharArray("日本語").GetPtr()));
      ASSERT_EQ(std::wstring(L""),
                std::wstring(WideCharArray("").GetPtr()));
    }

  }
}

#endif

