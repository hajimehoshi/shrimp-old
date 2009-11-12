#include "Shrimp/Views/MainWindow.h"
#include <cassert>

namespace Shrimp {
  namespace Views {

    MainWindow::MainWindow() : Handle(0) {
      const MainWindowWC& mainWindowWC = MainWindowWC::GetInstance();
      const WNDCLASSEX& wc = mainWindowWC.GetWndClass();
      CreateWindow(wc.lpszClassName,
                   _T("Shrimp"),
                   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                   CW_USEDEFAULT,
                   CW_USEDEFAULT,
                   CW_USEDEFAULT,
                   CW_USEDEFAULT,
                   0,
                   0,
                   GetModuleHandle(0),
                   this);
      // this->Handle is set on processing WM_NCCREATE
      assert(this->Handle);
    }

    void MainWindow::Show() {
      assert(this->Handle);
      ShowWindow(this->Handle, SW_SHOW);
      UpdateWindow(this->Handle);
    }

    LRESULT MainWindow::ProcessWindowMessage(UINT msg, WPARAM wp, LPARAM lp) {
      switch (msg) {
      case WM_PAINT:
        {
          LPCTSTR text = _T("ほげ");
          PAINTSTRUCT ps;
          BeginPaint(this->Handle, &ps);
          TextOut(ps.hdc, 10, 20, text, _tcslen(text));
          EndPaint(this->Handle, &ps);
          return 0;
        }
      case WM_LBUTTONDOWN:
        {
          MessageBox(this->Handle, _T("はい"), _T("Shrimp"), MB_ICONINFORMATION);
          return 0;
        }
      case WM_DESTROY:
        {
          PostQuitMessage(0);
          return 0;
        }
      }
      return DefWindowProc(this->Handle, msg, wp, lp);
    }

    LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
      if (msg == WM_NCCREATE) {
        MainWindow* const mainWindow =
          reinterpret_cast<MainWindow*>((reinterpret_cast<CREATESTRUCT*>(lp))->lpCreateParams);
        assert(mainWindow);
        mainWindow->Handle = hWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA,
                         reinterpret_cast<__int3264>(reinterpret_cast<LONG*>(mainWindow)));
      } else {
        MainWindow* const mainWindow =
          reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (!mainWindow) {
          return 1;
        }
        return mainWindow->ProcessWindowMessage(msg, wp, lp);
      }
      return DefWindowProc(hWnd, msg, wp, lp);
    }

    MainWindow::MainWindowWC::MainWindowWC() {
      WNDCLASSEX& wc = MainWindowWC::WndClass;
      ZeroMemory(&wc, sizeof(wc));
      wc.cbSize = sizeof(wc);
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = WndProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = GetModuleHandle(0);
      wc.hIcon = LoadIcon(0, IDI_APPLICATION);
      wc.hIconSm = LoadIcon(0, IDI_WINLOGO);
      wc.hCursor = LoadCursor(0, IDC_ARROW);
      wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
      wc.lpszMenuName = 0;
      wc.lpszClassName = _T("MainWindow");
      if (!RegisterClassEx(&wc)) {
        // exit?
      }
    }

  }
}
