#ifndef SHRIMP_VIEWS_BUTTON_H
#define SHRIMP_VIEWS_BUTTON_H

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class Button : private Util::Uncopyable {
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    private:
      static WNDCLASSEX wndClass;
      static WNDPROC defaultWndProc;
    public:
      Button(HWND parent);
      ~Button();
      void Show();
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
    };

  }
}

#endif
