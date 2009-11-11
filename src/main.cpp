#ifndef __TEST

#include <stdlib.h>
#include <windows.h>
#include "Shrimp/Application.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int showCmd) {
  Shrimp::Application& application = Shrimp::Application::GetInstance();
  return application.Run();;
}

#else

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
