#include "Shrimp/Application.h"
#include "Shrimp/Views/MainWindow.h"

namespace Shrimp {

  void Application::Run() {
    Views::MainWindow mainWindow;
    mainWindow.Show();
  }

}
