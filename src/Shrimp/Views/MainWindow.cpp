#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/MainWindow.h"
#include "Shrimp/Views/Button.h"
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    WNDCLASSEX MainWindow::wndClass;

    WNDPROC MainWindow::defaultWndProc;

    MainWindow::MainWindow()
      : handle(0) {
      if (!defaultWndProc) {
        defaultWndProc = ::DefWindowProc;
        ::ZeroMemory(&wndClass, sizeof(wndClass));
        wndClass.cbSize = sizeof(wndClass);
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = &WndProc<MainWindow>;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = GetModuleHandle(0);
        wndClass.hIcon = ::LoadIcon(0, IDI_APPLICATION);
        wndClass.hIconSm = ::LoadIcon(0, IDI_WINLOGO);
        wndClass.hCursor = ::LoadCursor(0, IDC_ARROW);
        wndClass.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
        wndClass.lpszMenuName = 0;
        wndClass.lpszClassName = _T("ShrimpMainWindow");
        if (!::RegisterClassEx(&wndClass)) {
          std::abort();
        }        
      }
      assert(defaultWndProc);
      ::CreateWindowEx(0,
                       wndClass.lpszClassName,
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
      Button* button = new Button(this->handle);
      button->Show();
      Models::MapCollection* mapCollection = new Models::MapCollection();
      MapTreeView* mapTreeView = new MapTreeView(this->handle);
      Presenters::MapTreeViewPresenter<MapTreeView>* presenter =
        new Presenters::MapTreeViewPresenter<MapTreeView>(*mapCollection, *mapTreeView);
      assert(presenter); // to cancel warining
      mapTreeView->Show();
    }

    MainWindow::~MainWindow() throw() {
      ::DestroyWindow(this->handle);
    }

    void MainWindow::Show() {
      ::ShowWindow(this->handle, SW_SHOW);
      ::UpdateWindow(this->handle);
    }

    LRESULT MainWindow::ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
      switch (msg) {
      case WM_PAINT:
        {
          const TCHAR* text = _T("ほげ");
          PAINTSTRUCT ps;
          ::BeginPaint(this->handle, &ps);
          ::TextOut(ps.hdc, 400, 400, text, _tcslen(text));
          ::EndPaint(this->handle, &ps);
          return 0;
        }
        break;
      case WM_LBUTTONDOWN:
        {
          ::MessageBox(this->handle,
                       _T("ウィンドウがクリックされた"),
                       _T("Shrimp"),
                       MB_ICONINFORMATION);
          return 0;
        }
        break;
      case WM_DESTROY:
        {
          ::PostQuitMessage(0);
          return 0;
        }
      }
      return defaultWndProc(this->handle, msg, wParam, lParam);
    }

  }
}
