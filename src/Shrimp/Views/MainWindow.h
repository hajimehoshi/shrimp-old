#ifndef SHRIMP_VIEWS_MAINWINDOW_H
#define SHRIMP_VIEWS_MAINWINDOW_H

#include <windows.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"

namespace Shrimp {
  namespace Views {

    class MainWindow {
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    public:
      MainWindow();
      void Show();
    private:
      MainWindow(const MainWindow& rhs);
      MainWindow& operator=(const MainWindow& rhs);
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND Handle;
    private:

      class MainWindowWC {
      public:
        const WNDCLASSEX& GetWndClass() const {
          return this->WndClass;
        }
      private:
        MainWindowWC();
        MainWindowWC(const MainWindowWC& rhs);
        MainWindowWC& operator=(const MainWindowWC& rhs);
        WNDCLASSEX WndClass;
      public:
        static const MainWindowWC& GetInstance() {
          static const MainWindowWC instance;
          return instance;
        }
      };

    };

  }
}

#endif
