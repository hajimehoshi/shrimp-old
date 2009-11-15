#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <string>

namespace Shrimp {
  namespace Models {

    class Map {
    public:
      Map(std::string name, int width, int height);
      inline int GetHeight() {
        return this->Height;
      }
      inline const std::string& GetName() {
        return this->Name;
      }
      inline int GetWidth() {
        return this->Width;
      }
    private:
      Map(const Map& map);
      Map& operator=(const Map& rhs);
      std::string Name;
      int Width;
      int Height;
    };


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


#endif
