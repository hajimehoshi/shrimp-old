#ifndef SHRIMP_VIEWS_MAINWINDOW_H
#define SHRIMP_VIEWS_MAINWINDOW_H

#include <windows.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Singleton.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class MainWindow : private Util::Uncopyable {
    private:
      class MainWindowWC : public Util::Singleton<MainWindowWC> {
        friend class Util::Singleton<MainWindowWC>;
      public:
        const WNDCLASSEX& GetWndClass() const {
          return this->wndClass;
        }
      private:
        MainWindowWC();
        WNDCLASSEX wndClass;
      };
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    public:
      MainWindow();
      void Show();
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
    };

  }
}

#endif
