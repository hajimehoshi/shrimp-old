#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    MapCollection::Node::Node(int id,
                              int parentId,
                              MapCollection::NodeType nodeType,
                              Models::Map* map)
      : Id(id), ParentId(parentId), NodeType(nodeType), Map(map) {
    }

    MapCollection::MapCollection()
      : NextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(id, -1, NodeTypeProject, 0);
      this->Nodes.insert(std::make_pair(id, node));
      this->ProjectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(id, -1, NodeTypeRecycleBin, 0);
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

    MapCollection::NodeType MapCollection::GetNodeType(int id) const {
      std::map<int, Node*>::const_iterator it = this->Nodes.find(id);
      assert(it != this->Nodes.end());
      return (*it).second->NodeType;
    }

    int MapCollection::GetProjectNodeId() const {
      return this->ProjectNodeId;
    }

    int MapCollection::GetRecycleBinNodeId() const {
      return this->RecycleBinNodeId;
    }

    int MapCollection::GenerateNextId() {
      int nextId = this->NextId;
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

      ASSERT_EQ(MapCollection::NodeTypeProject,
                mapCollection.GetNodeType(0));
      ASSERT_EQ(MapCollection::NodeTypeRecycleBin,
                mapCollection.GetNodeType(1));
    }

    /*TEST(MapCollectionTest, AddMap) {
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
     }*/

  }
}

#endif
