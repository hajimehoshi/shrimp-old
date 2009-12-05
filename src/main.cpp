#ifdef __TEST
# include <gtest/gtest.h>
#endif
#include "Shrimp/Application.h"


#ifndef __TEST

int main() {
  Shrimp::Application& application = Shrimp::Application::GetInstance();
  return application.Run();
}

#else

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
