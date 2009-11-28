#ifndef SHRIMP_VIEWS_BUTTON_H
#define SHRIMP_VIEWS_BUTTON_H

#include <windows.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Singleton.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class Button : private Util::Uncopyable {
    private:
      class ButtonWC : public Util::Singleton<ButtonWC> {
        friend class Util::Singleton<ButtonWC>;
      public:
        const WNDCLASSEX& GetWndClass() const {
          return this->wndClass;
        }
        inline const WNDPROC GetDefaultWndProc() const {
          assert(this->defaultWndProc);
          return this->defaultWndProc;
        }
      private:
        ButtonWC();
        WNDCLASSEX wndClass;
        WNDPROC defaultWndProc;
      };

      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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
