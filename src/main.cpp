#ifdef __TEST
# include <gtest/gtest.h>
#endif
#include "Shrimp/Application.h"

int main(int argc, char** argv) {
#ifdef __TEST
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  Shrimp::Application& application = Shrimp::Application::GetInstance();
  return application.Run();
#endif
}
