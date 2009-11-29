#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/Button.h"

namespace Shrimp {
  namespace Views {

    Button::Button(HWND parent)
      : handle(0) {
      const ButtonWC& buttonWC = ButtonWC::GetInstance();
      const WNDCLASSEX& wc = buttonWC.GetWndClass();
      CreateWindowEx(0,
                     wc.lpszClassName,
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

    Button::~Button() {
      DestroyWindow(this->handle);
    }

    void Button::Show() {
      assert(this->handle);
      ShowWindow(this->handle, SW_SHOW);
      UpdateWindow(this->handle);
    }

    LRESULT Button::ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
      switch (msg) {
      case WM_LBUTTONUP:
        {
          MessageBox(this->handle, _T("ボタンがクリックされた"), _T("Shrimp"), MB_ICONINFORMATION);
        }
        break;
      }
      const ButtonWC& buttonWC = ButtonWC::GetInstance();
      return buttonWC.GetDefaultWndProc()(this->handle, msg, wParam, lParam);
    }

    ButtonWC::ButtonWC()
      : defaultWndProc(0) {
      WNDCLASSEX& wc = this->wndClass;
      ZeroMemory(&wc, sizeof(wc));
      wc.cbSize = sizeof(wc);
      GetClassInfoEx(0, WC_BUTTON, &wc);
      this->defaultWndProc = wc.lpfnWndProc;
      wc.lpfnWndProc = &WndProc<Button>;
      wc.lpszClassName = _T("ShrimpButton");
      if (!RegisterClassEx(&wc)) {
        std::abort();
      }
    }

  }
}
