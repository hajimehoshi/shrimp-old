#ifndef SHRIMP_VIEWS_WNDPROC_H
#define SHRIMP_VIEWS_WNDPROC_H

#include <cassert>
#include <windows.h>
#include <tchar.h>

namespace Shrimp {
  namespace Views {

    template<class TControl>
      LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
      if (msg == WM_NCCREATE) {
        TControl* const control =
          reinterpret_cast<TControl*>((reinterpret_cast<CREATESTRUCT*>(lParam))->lpCreateParams);
        assert(control);
        control->Handle = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA,
                         reinterpret_cast<__int3264>(reinterpret_cast<LONG*>(control)));
      } else {
        TControl* const control =
          reinterpret_cast<TControl*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (control) {
          return control->ProcessWindowMessage(msg, wParam, lParam);
        }
      }
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }

  }
}

#endif
