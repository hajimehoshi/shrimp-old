#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    Map::Map(std::string name, int width, int height)
      : Name(name), Width(width), Height(height) {
    }

    void Map::SetHeight(int height) {
      this->Height = height;
    }

    void Map::SetName(std::string name) {
      this->Name = name;
    }

    void Map::SetWidth(int width) {
      this->Width = width;
    }

  }
}


#if __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    /*class MapMockObserver {
    public:
      
    };*/

    TEST(Map, Name) {
      Map map("Foo", 20, 15);
      ASSERT_EQ("Foo", map.GetName());
      map.SetName("Bar");
      ASSERT_EQ("Bar", map.GetName());
    }

    TEST(Map, Width) {
      Map map("Foo", 20, 15);
      ASSERT_EQ(20, map.GetWidth());
      map.SetWidth(21);
      ASSERT_EQ(21, map.GetWidth());
    }

    TEST(Map, Height) {
      Map map("Foo", 20, 15);
      ASSERT_EQ(15, map.GetHeight());
      map.SetHeight(16);
      ASSERT_EQ(16, map.GetHeight());
    }

  }

}

#endif
