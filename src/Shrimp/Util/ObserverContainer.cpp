#ifdef __TEST

#include "Shrimp/Util/ObserverContainer.h"

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Util {

    TEST(ObserverContainerTest, Foo) {
      ObserverContainer<int> container;
      container.Add(3);
      container.Add(1);
      container.Add(4);
      container.Remove(1);
      container.Add(5);
      container.Add(9);
      container.Add(2);
      container.Add(6);
      container.Remove(5);
      container.Remove(3);
      
      std::set<int> expected;
      expected.insert(2);
      expected.insert(4);
      expected.insert(6);
      expected.insert(9);

      std::set<int> actual;
      std::copy(container.Begin(), container.End(),
                std::inserter(actual, actual.end()));

      ASSERT_TRUE(expected == actual);
    }

  }
}

#endif
