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
      MainWindow(const MainWindow& rhs);
      MainWindow& operator=(const MainWindow& rhs);
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wp, LPARAM lp);
      HWND Handle;
    private:
      static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

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
