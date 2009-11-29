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
    while (BOOL r = GetMessage(&msg, 0, 0, 0)) {
      assert(r != -1);
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return msg.wParam;
  }

}
