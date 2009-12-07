#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/Button.h"

namespace Shrimp {
  namespace Views {

    WNDCLASSEX Button::wndClass;

    WNDPROC Button::defaultWndProc;

    Button::Button(HWND parent)
      : handle(0) {
      if (!defaultWndProc) {
        ::ZeroMemory(&wndClass, sizeof(wndClass));
        wndClass.cbSize = sizeof(wndClass);
        ::GetClassInfoEx(0, WC_BUTTON, &wndClass);
        defaultWndProc = wndClass.lpfnWndProc;
        wndClass.lpfnWndProc = &WndProc<Button>;
        wndClass.lpszClassName = _T("ShrimpButton");
        if (!::RegisterClassEx(&wndClass)) {
          std::abort();
        }
      }
      assert(defaultWndProc);
      ::CreateWindowEx(0,
                       wndClass.lpszClassName,
                       _T("OK"),
                       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                       10, 10, 100, 100,
                       parent,
                       0,
                       GetModuleHandle(0),
                       this);
      // this->handle is set on processing WM_NCCREATE in WndProc
      assert(this->handle);
    }

    Button::~Button() throw() {
      ::DestroyWindow(this->handle);
    }

    void Button::Show() {
      ::ShowWindow(this->handle, SW_SHOW);
      ::UpdateWindow(this->handle);
    }

    LRESULT Button::ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
      switch (msg) {
      case WM_LBUTTONUP:
        {
          ::MessageBox(this->handle,
                       _T("ボタンがクリックされた"),
                       _T("Shrimp"),
                       MB_ICONINFORMATION);
        }
        break;
      }
      return defaultWndProc(this->handle, msg, wParam, lParam);
    }

  }
}
