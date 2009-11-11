#include "Shrimp/Application.h"
#include "Shrimp/Views/MainWindow.h"
#include <windows.h>

namespace Shrimp {

  int Application::Run() {
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
