#include "Shrimp/Application.h"
#include "Shrimp/Views/MainWindow.h"
#include <windows.h>
#include <commctrl.h>

namespace Shrimp {

  int Application::Run() {
    InitCommonControls();
    Views::MainWindow mainWindow;
    mainWindow.Show();
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return msg.wParam;
  }

}
