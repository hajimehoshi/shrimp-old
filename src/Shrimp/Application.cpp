#include "Shrimp/Application.h"
#include "Shrimp/Views/MainWindow.h"
#include <windows.h>

namespace Shrimp {

  void Application::Run() {
    Views::MainWindow mainWindow;
    mainWindow.Show();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

}
