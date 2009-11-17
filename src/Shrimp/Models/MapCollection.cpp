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

      id = this->GenerateNextId();
      Node* recycleBinNode = new Node(id, -1, NodeTypeRecycleBin, 0);
      this->Nodes.insert(std::make_pair(id, recycleBinNode));
      RootNodeIds[0] = id;

      id = this->GenerateNextId();
      Node* projectNode = new Node(id, -1, NodeTypeProject, 0);
      this->Nodes.insert(std::make_pair(id, projectNode));
      RootNodeIds[1] = id;
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

    int MapCollection::GetRootNodeCount() const {
      return sizeof(this->RootNodeIds) / sizeof(this->RootNodeIds[0]);
    }

    void MapCollection::GetRootNodeIds(int* rootNodeIds) const {
      for (int i = 0; i < this->GetRootNodeCount(); ++i) {
        rootNodeIds[i] = this->RootNodeIds[i];
      }
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

      int rootNodeCount = mapCollection.GetRootNodeCount();
      ASSERT_EQ(2, rootNodeCount);

      int* rootNodeIds = new int[rootNodeCount];
      mapCollection.GetRootNodeIds(rootNodeIds);
      ASSERT_EQ(0, rootNodeIds[0]);
      ASSERT_EQ(1, rootNodeIds[1]);
      delete[] rootNodeIds;

      ASSERT_EQ(MapCollection::NodeTypeRecycleBin,
                mapCollection.GetNodeType(0));
      ASSERT_EQ(MapCollection::NodeTypeProject,
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
