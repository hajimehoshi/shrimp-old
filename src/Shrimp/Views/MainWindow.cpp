#include "Shrimp/Views/MainWindow.h"

namespace Shrimp {
  namespace Views {

    MainWindow::MainWindow() : Handle(NULL) {
      HINSTANCE hInstance = GetModuleHandle(NULL);
      WNDCLASSEX wc;
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
      wc.lpszClassName = _T("Default Class Name");
      if (RegisterClassEx(&wc) == 0) {
        // exit?
      }
      this->Handle = CreateWindow(wc.lpszClassName,
                                  _T("Sample Program"),
                                  WS_OVERLAPPEDWINDOW,
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
      switch (msg) {
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
      }
      return DefWindowProc(hWnd, msg, wp, lp);
    }

  }
}
