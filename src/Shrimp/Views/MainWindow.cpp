#include "Shrimp/Views/MainWindow.h"

namespace Shrimp {
  namespace Views {

    MainWindow::MainWindow() : Handle(NULL) {
      HINSTANCE hInstance = GetModuleHandle(NULL);
      WNDCLASSEX wc;
      ZeroMemory(&wc, sizeof(wc));
      wc.cbSize = sizeof(wc);
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = MainWindow::WndProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = hInstance;
      wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
      wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
      wc.lpszMenuName = NULL;
      wc.lpszClassName = _T("MainWindow");
      if (RegisterClassEx(&wc) == 0) {
        // exit?
      }
      this->Handle = CreateWindow(wc.lpszClassName,
                                  _T("Shrimp"),
                                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  NULL);
      if (this->Handle == NULL) {
        // exit?
      }
    }

    void MainWindow::Show() {
      ShowWindow(this->Handle, SW_SHOW);
      UpdateWindow(this->Handle);
    }

    LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
      LPCTSTR text = _T("ほげ");
      PAINTSTRUCT ps;
      switch (msg) {
      case WM_PAINT:
        BeginPaint(hWnd, &ps);
        TextOut(ps.hdc, 10, 20, text, _tcslen(text));
        EndPaint(hWnd, &ps);
        break;
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(hWnd, msg, wp, lp);        
      }
      return 0;
    }

  }
}
