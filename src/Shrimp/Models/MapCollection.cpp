#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    MapCollection::Node::Node(int id,
                              int parentId,
                              Models::Map* map)
      : Id(id), ParentId(parentId), Map(map) {
    }

    MapCollection::MapCollection()
      : NextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(id, -1, 0);
      this->Nodes.insert(std::make_pair(id, node));
      this->ProjectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(id, -1, 0);
      this->Nodes.insert(std::make_pair(id, node));
      this->RecycleBinNodeId = id;
    }

    MapCollection::~MapCollection() {
      for (std::map<int, Node*>::iterator it = this->Nodes.begin();
           it != this->Nodes.end();
           ++it) {
        delete (*it).second;
      }
      this->Nodes.clear();
    }

    void MapCollection::Add(int parentId, Map* const map) {
      int id = this->GenerateNextId();
      Node* node = new Node(id, parentId, map);
      this->Nodes.insert(std::make_pair(id, node));
    }

    int MapCollection::GetChildNodeCount(int id) const {
      // TODO: optimize following codes!
      int count = 0;
      for (std::map<int, Node*>::const_iterator it = this->Nodes.begin();
           it != this->Nodes.end();
           ++it) {
        if ((*it).second->ParentId == id) {
          count++;
        }
      }
      return count;
    }

    int MapCollection::GetProjectNodeId() const {
      return this->ProjectNodeId;
    }

    int MapCollection::GetRecycleBinNodeId() const {
      return this->RecycleBinNodeId;
    }

    int MapCollection::GenerateNextId() {
      const int nextId = this->NextId;
      this->NextId++;
      return nextId;
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    TEST(MapCollectionTest, RootNodes) {
      MapCollection mapCollection;
      ASSERT_EQ(0, mapCollection.GetProjectNodeId());
      ASSERT_EQ(1, mapCollection.GetRecycleBinNodeId());
    }

    TEST(MapCollectionTest, Add) {
      MapCollection mapCollection;
      Map map1("Foo", 20, 15);
      Map map2("Bar", 21, 16);
      Map map3("Baz", 22, 17);

      const int projectNodeId = mapCollection.GetProjectNodeId();
      const int recycleBinNodeId = mapCollection.GetRecycleBinNodeId();

      ASSERT_EQ(0, mapCollection.GetChildNodeCount(projectNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(recycleBinNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(2));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(3));

      mapCollection.Add(projectNodeId, &map1);
      ASSERT_EQ(1, mapCollection.GetChildNodeCount(projectNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(recycleBinNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(2));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(3));

      mapCollection.Add(projectNodeId, &map2);
      ASSERT_EQ(2, mapCollection.GetChildNodeCount(projectNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(recycleBinNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(2));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(3));

      mapCollection.Add(3, &map3);
      ASSERT_EQ(2, mapCollection.GetChildNodeCount(projectNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(recycleBinNodeId));
      ASSERT_EQ(0, mapCollection.GetChildNodeCount(2));
      ASSERT_EQ(1, mapCollection.GetChildNodeCount(3));

      /*
      const Map& tmpMap1 = mapCollection.GetMap(0);
      ASSERT_EQ(&map1, &tmpMap1);
      const Map& tmpMap2 = mapCollection.GetMap(1);
      ASSERT_EQ(&map2, &tmpMap2);*/
    }

  }
}

#endif
