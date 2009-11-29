#ifndef SHRIMP_VIEWS_WNDPROC_H
#define SHRIMP_VIEWS_WNDPROC_H

#include <cassert>
#include <windows.h>

namespace Shrimp {
  namespace Views {

    template<class TControl>
      LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
      if (msg == WM_NCCREATE) {
        const CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        TControl* const control =
          reinterpret_cast<TControl*>(createStruct->lpCreateParams);
        assert(control);
        control->handle = hWnd;
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<__int3264>(control));
      } else {
        TControl* const control =
          reinterpret_cast<TControl*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (control) {
          return control->ProcessWindowMessage(msg, wParam, lParam);
        }
      }
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

  }
}

#endif
