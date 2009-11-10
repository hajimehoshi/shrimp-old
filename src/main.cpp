#ifndef __TEST

#include <iostream>
#include "Shrimp/Application.h"

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}

#else

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif
