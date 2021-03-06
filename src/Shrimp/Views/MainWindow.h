#ifndef SHRIMP_VIEWS_MAINWINDOW_H
#define SHRIMP_VIEWS_MAINWINDOW_H

#include <windows.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class MainWindow : private Util::Uncopyable {
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    private:
      static WNDCLASSEX wndClass;
      static WNDPROC defaultWndProc;
    public:
      MainWindow();
      ~MainWindow() throw();
      void Show();
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
    };

  }
}

#endif
