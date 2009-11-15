#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    Map::Map(std::string name, int width, int height)
      : Name(name), Width(width), Height(height) {
    }

  }
}


#if __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    TEST(Map, Map) {
      Map map("Foo", 20, 15);
      ASSERT_EQ("Foo", map.GetName());
      ASSERT_EQ(20, map.GetWidth());
      ASSERT_EQ(15, map.GetHeight());
    }

  }

}

#endif
