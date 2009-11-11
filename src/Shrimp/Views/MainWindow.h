#ifndef SHRIMP_VIEWS_MAINWINDOW
#define SHRIMP_VIEWS_MAINWINDOW

#include <windows.h>
#include <tchar.h>

namespace Shrimp {
  namespace Views {
    class MainWindow {
    public:
      MainWindow();
      void Show();
    private:
      HWND Handle;
    private:
      static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
    };
  }
}

#endif
