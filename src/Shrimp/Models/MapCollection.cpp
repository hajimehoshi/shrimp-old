#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    MapCollection::MapCollection() {
    }

    void MapCollection::Add(Map& map) {
      this->Maps.push_back(&map);
    }

    Map& MapCollection::GetMap(int index) const {
      assert(0 <= index);
      assert(index < this->GetMapCount());
      return *(this->Maps[index]);
    }

    int MapCollection::GetMapCount() const {
      return this->Maps.size();
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    TEST(MapCollectionTest, AddMap) {
      MapCollection mapCollection;
      Map map1("Foo", 20, 15);
      Map map2("Bar", 21, 16);
      mapCollection.Add(map1);
      mapCollection.Add(map2);
      ASSERT_EQ(2, mapCollection.GetMapCount());
      const Map& tmpMap1 = mapCollection.GetMap(0);
      ASSERT_EQ(&map1, &tmpMap1);
      const Map& tmpMap2 = mapCollection.GetMap(1);
      ASSERT_EQ(&map2, &tmpMap2);
    }

  }
}

#endif
