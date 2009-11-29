#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/MainWindow.h"
#include "Shrimp/Views/Button.h"
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    MainWindow::MainWindow()
      : handle(0) {
      const MainWindowWC& mainWindowWC = MainWindowWC::GetInstance();
      const WNDCLASSEX& wc = mainWindowWC.GetWndClass();
      CreateWindowEx(0,
                     wc.lpszClassName,
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
      // this->handle is set on processing WM_NCCREATE in WndProc
      assert(this->handle);
    }

    MainWindow::~MainWindow() {
      DestroyWindow(this->handle);
    }

    void MainWindow::Show() {
      assert(this->handle);
      ShowWindow(this->handle, SW_SHOW);
      UpdateWindow(this->handle);
    }

    LRESULT MainWindow::ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
      switch (msg) {
      case WM_CREATE:
        {
          Button* button = new Button(this->handle);
          button->Show();
          MapTreeView* mapTreeView = new MapTreeView(this->handle);
          mapTreeView->Show();
          return 0;
        }
      case WM_PAINT:
        {
          const TCHAR* text = _T("ほげ");
          PAINTSTRUCT ps;
          BeginPaint(this->handle, &ps);
          TextOut(ps.hdc, 400, 400, text, _tcslen(text));
          EndPaint(this->handle, &ps);
          return 0;
        }
      case WM_LBUTTONDOWN:
        {
          MessageBox(this->handle, _T("ウィンドウがクリックされた"), _T("Shrimp"), MB_ICONINFORMATION);
          return 0;
        }
      case WM_DESTROY:
        {
          PostQuitMessage(0);
          return 0;
        }
      }
      const MainWindowWC& mainWindowWC = MainWindowWC::GetInstance();
      return mainWindowWC.GetDefaultWndProc()(this->handle, msg, wParam, lParam);
    }

    MainWindowWC::MainWindowWC()
      : defaultWndProc(DefWindowProc) {
      WNDCLASSEX& wc = this->wndClass;
      ZeroMemory(&wc, sizeof(wc));
      wc.cbSize = sizeof(wc);
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = &WndProc<MainWindow>;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = GetModuleHandle(0);
      wc.hIcon = LoadIcon(0, IDI_APPLICATION);
      wc.hIconSm = LoadIcon(0, IDI_WINLOGO);
      wc.hCursor = LoadCursor(0, IDC_ARROW);
      wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
      wc.lpszMenuName = 0;
      wc.lpszClassName = _T("ShrimpMainWindow");
      if (!RegisterClassEx(&wc)) {
        std::abort();
      }
    }

  }
}
