#ifndef __TEST

#include <stdlib.h>
#include <iostream>
#include "Shrimp/Application.h"

int main() {
  Shrimp::Application application;
  application.Run();
  return EXIT_SUCCESS;
}

#else

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
