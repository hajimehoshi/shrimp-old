#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    MapCollection::Node::Node(int parentId, Models::Map* map)
      : ParentId(parentId), Map(map) {
    }

    MapCollection::MapCollection()
      : NextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(Node::InvalidId, 0);
      this->Nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->ProjectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(Node::InvalidId, 0);
      this->Nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->RecycleBinNodeId = id;
    }

    MapCollection::~MapCollection() {
      for (std::map<int, Node*>::iterator it = this->Nodes.begin();
           it != this->Nodes.end();
           ++it) {
        delete it->second;
      }
      this->Nodes.clear();
    }

    void MapCollection::Add(int parentId, Map& map) {
      int id = this->GenerateNextId();
      Node* node = new Node(parentId, &map);
      this->Nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->GetNode(parentId)->ChildIds.insert(id);
    }

    const std::set<int>& MapCollection::GetChildIds(int id) const {
      return this->GetNode(id)->ChildIds;
    }

    Map& MapCollection::GetMap(int id) const {
      return *(this->GetNode(id)->Map);
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

    MapCollection::Node* MapCollection::GetNode(int id) const {
      std::map<int, Node*>::const_iterator it = this->Nodes.find(id);
      assert(it != this->Nodes.end());
      return it->second;
    }

    IMapCollectionObserver::~IMapCollectionObserver() {
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    class MockMapCollectionObserver : public IMapCollectionObserver {
    public:
      MockMapCollectionObserver() {
        this->Clear();
      }
      virtual ~MockMapCollectionObserver() { }
      void Clear() {
        this->IsCalledOnItemAdded = false;
      }
      virtual void OnItemAdded() {
        this->IsCalledOnItemAdded = true;
      }
      bool IsCalledOnItemAdded;
    };

    TEST(MapCollectionTest, RootNodes) {
      MapCollection mapCollection;
      ASSERT_EQ(0, mapCollection.GetProjectNodeId());
      ASSERT_EQ(1, mapCollection.GetRecycleBinNodeId());
    }

    TEST(MapCollectionTest, Add) {
      MapCollection mapCollection;
      MockMapCollectionObserver mapCollectionObserver;
      mapCollection.AddObserver(mapCollectionObserver);

      Map map1("Foo", 20, 15);
      Map map2("Bar", 21, 16);
      Map map3("Baz", 22, 17);

      std::set<int> expectedIds;

      ASSERT_TRUE(mapCollection.GetChildIds(0).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());

      mapCollection.Add(0, map1);
      expectedIds.clear();
      expectedIds.insert(2);
      ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(2).empty());

      mapCollection.Add(0, map2);
      expectedIds.clear();
      expectedIds.insert(2);
      expectedIds.insert(3);
      ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(3).empty());

      mapCollection.Add(3, map3);
      expectedIds.clear();
      expectedIds.insert(2);
      expectedIds.insert(3);
      ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
      expectedIds.clear();
      expectedIds.insert(4);
      ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(3));
      ASSERT_TRUE(mapCollection.GetChildIds(4).empty());

      const Map& tmpMap1 = mapCollection.GetMap(2);
      ASSERT_EQ(&map1, &tmpMap1);
      const Map& tmpMap2 = mapCollection.GetMap(3);
      ASSERT_EQ(&map2, &tmpMap2);
      const Map& tmpMap3 = mapCollection.GetMap(4);
      ASSERT_EQ(&map3, &tmpMap3);
    }

  }
}

#endif
