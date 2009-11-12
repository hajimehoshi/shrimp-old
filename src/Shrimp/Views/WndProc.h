#ifndef SHRIMP_VIEWS_WNDPROC
#define SHRIMP_VIEWS_WNDPROC

#include <cassert>
#include <windows.h>
#include <tchar.h>

namespace Shrimp {
  namespace Views {

    template<class TControl>
      LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
      if (msg == WM_NCCREATE) {
        TControl* const control =
          reinterpret_cast<TControl*>((reinterpret_cast<CREATESTRUCT*>(lp))->lpCreateParams);
        assert(control);
        control->Handle = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA,
                         reinterpret_cast<__int3264>(reinterpret_cast<LONG*>(control)));
      } else {
        TControl* const control =
          reinterpret_cast<TControl*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (!control) {
          return 1;
        }
        return control->ProcessWindowMessage(msg, wp, lp);
      }
      return DefWindowProc(hWnd, msg, wp, lp);
    }

  }
}

#endif
