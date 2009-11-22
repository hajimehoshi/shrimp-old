#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    typedef Util::ObserverContainer<IMapCollectionObserver*>::Observers Observers;

    MapCollection::Node::Node(int parentId, Models::Map* map)
      : ParentId(parentId), Map(map) {
    }

    MapCollection::MapCollection()
      : nextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(Node::InvalidId, 0);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->projectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(Node::InvalidId, 0);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->recycleBinNodeId = id;
    }

    MapCollection::~MapCollection() {
      for (std::map<int, Node*>::iterator it = this->nodes.begin();
           it != this->nodes.end();
           ++it) {
        delete it->second;
      }
      this->nodes.clear();
    }

    void MapCollection::Add(int parentId, Map& map) {
      int id = this->GenerateNextId();
      Node* node = new Node(parentId, &map);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->GetNode(parentId)->ChildIds.insert(id);
      const Observers& e = this->observers.GetObservers();
      for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
        (*it)->OnItemAdded(id);
      }
    }

    const std::set<int>& MapCollection::GetChildIds(int id) const {
      return this->GetNode(id)->ChildIds;
    }

    Map& MapCollection::GetMap(int id) const {
      return *(this->GetNode(id)->Map);
    }

    int MapCollection::GetProjectNodeId() const {
      return this->projectNodeId;
    }

    int MapCollection::GetRecycleBinNodeId() const {
      return this->recycleBinNodeId;
    }

    int MapCollection::GenerateNextId() {
      const int nextId = this->nextId;
      this->nextId++;
      return nextId;
    }

    MapCollection::Node* MapCollection::GetNode(int id) const {
      std::map<int, Node*>::const_iterator it = this->nodes.find(id);
      assert(it != this->nodes.end());
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
      virtual ~MockMapCollectionObserver() { }
      virtual void OnItemAdded(int index) {
        this->calledHandler = "OnItemAdded";
        this->intValues["index"] = index;
      }
      std::string calledHandler;
      std::map<std::string, int> intValues;
    };

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

      ASSERT_TRUE(mapCollection.GetChildIds(0).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());

      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(0, map1);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(2, observer.intValues["index"]);
        mapCollection.RemoveObserver(observer);
      }

      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(0, map2);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        expectedIds.insert(3);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(3).empty());
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(3, observer.intValues["index"]);
        mapCollection.RemoveObserver(observer);
      }

      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(3, map3);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        expectedIds.insert(3);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        expectedIds.clear();
        expectedIds.insert(4);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(3));
        ASSERT_TRUE(mapCollection.GetChildIds(4).empty());
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(4, observer.intValues["index"]);
        mapCollection.RemoveObserver(observer);
      }

      const Map& tmpMap1 = mapCollection.GetMap(2);
      ASSERT_EQ(&map1, &tmpMap1);
      const Map& tmpMap2 = mapCollection.GetMap(3);
      ASSERT_EQ(&map2, &tmpMap2);
      const Map& tmpMap3 = mapCollection.GetMap(4);
      ASSERT_EQ(&map3, &tmpMap3);
    }

    /*TEST(MapCollectionTest, Remove) {
      MapCollection mapCollection;
      Map map1("Foo", 20, 15);
      Map map2("Bar", 21, 16);
      Map map3("Baz", 22, 17);

      mapCollection.Add(0, map1); // 2
      mapCollection.Add(0, map2); // 3
      mapCollection.Add(3, map3); // 4

      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Remove(3);
        std::set<int> expectedIds;
        expectedIds.insert();
        ASSERT_TURE(expectedIds == mapCollection.GetChildIds(0));
        mapCollection.RemoveObserver(observer);
      }
      }*/

  }
}

#endif
