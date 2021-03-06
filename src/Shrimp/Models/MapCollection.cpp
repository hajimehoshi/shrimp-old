#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    MapCollection::Node::Node(int id, int parentId)
      : map(id), parentId(parentId) {
    }

    MapCollection::MapCollection()
      : nextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(id, Node::InvalidId);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->projectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(id, Node::InvalidId);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->recycleBinNodeId = id;
    }

    MapCollection::~MapCollection() throw() {
      for (std::map<int, Node*>::iterator it = this->nodes.begin();
           it != this->nodes.end();
           ++it) {
        // TODO: Refactoring
        if (it->second->parentId != Node::InvalidId) {
          it->second->map.RemoveObserver(*this);
        }
        delete it->second;
      }
      this->nodes.clear();
    }

    void MapCollection::Add(int parentId) {
      int id = this->GenerateNextId();
      Node* node = new Node(id, parentId);
      node->map.AddObserver(*this);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->GetNode(parentId)->childIds.insert(id);
      for (Observers::const_iterator it = this->observers.begin();
           it != this->observers.end();
           ++it) {
        (*it)->MapCollection_ItemAdded(*this, id);
      }
    }

    const MapCollection::ChildIds& MapCollection::GetChildIds(int id) const {
      return this->GetNode(id)->childIds;
    }

    Map& MapCollection::GetMap(int id) const {
      return this->GetNode(id)->map;
    }

    int MapCollection::GetParentId(int id) const {
      return this->GetNode(id)->parentId;
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

    void MapCollection::Map_NameUpdated(Map& map) {
      int id = map.GetId();
      assert(&(this->GetMap(id)) == &map);
      for (Observers::const_iterator it = this->observers.begin();
           it != this->observers.end();
           ++it) {
        (*it)->MapCollection_ItemNameUpdated(*this, id);
      }
    }

    void MapCollection::Remove(int id) {
      Node* node = this->GetNode(id);
      Node* parentNode = this->GetNode(node->parentId);
      std::set<int>::iterator it = parentNode->childIds.find(id);
      assert(it != parentNode->childIds.end());
      parentNode->childIds.erase(it);
      this->RemoveNode(id);
      for (Observers::const_iterator it = this->observers.begin();
           it != this->observers.end();
           ++it) {
        (*it)->MapCollection_ItemRemoved(*this, id);
      }
    }

    void MapCollection::RemoveNode(int id) {
      std::map<int, Node*>::iterator it = this->nodes.find(id);
      assert(it != this->nodes.end());
      Node* node = it->second;
      std::set<int> childIds = node->childIds;
      for (std::set<int>::iterator it2 = childIds.begin();
           it2 != childIds.end();
           ++it2) {
        this->RemoveNode(*it2);
      }
      this->nodes.erase(it);
      node->map.RemoveObserver(*this);
      delete node;
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    class MockMapCollectionObserver : public IMapCollectionObserver {
    public:
      ~MockMapCollectionObserver() throw() { }
      void MapCollection_ItemAdded(MapCollection& mapCollection, int id) {
        this->calledHandler = "MapCollection_ItemAdded";
        this->mapCollectionValues["mapCollection"] = &mapCollection;
        this->intValues["id"] = id;
      }
      void MapCollection_ItemNameUpdated(MapCollection& mapCollection, int id) {
        this->calledHandler = "MapCollection_ItemNameUpdated";
        this->mapCollectionValues["mapCollection"] = &mapCollection;
        this->intValues["id"] = id;
      }
      void MapCollection_ItemRemoved(MapCollection& mapCollection, int id) {
        this->calledHandler = "MapCollection_ItemRemoved";
        this->mapCollectionValues["mapCollection"] = &mapCollection;
        this->intValues["id"] = id;
      }
      std::string calledHandler;
      std::map<std::string, int> intValues;
      std::map<std::string, MapCollection*> mapCollectionValues;
    };

    TEST(MapCollectionTest, RootNodes) {
      MapCollection mapCollection;
      ASSERT_EQ(0, mapCollection.GetProjectNodeId());
      ASSERT_EQ(1, mapCollection.GetRecycleBinNodeId());
    }

    TEST(MapCollectionTest, GetParentId) {
      MapCollection mapCollection;
      mapCollection.Add(0); // 2
      mapCollection.Add(0); // 3
      mapCollection.Add(3); // 4
      ASSERT_EQ(0, mapCollection.GetParentId(2));
      ASSERT_EQ(0, mapCollection.GetParentId(3));
      ASSERT_EQ(3, mapCollection.GetParentId(4));
    }

    TEST(MapCollectionTest, Add) {
      MapCollection mapCollection;
      ASSERT_TRUE(mapCollection.GetChildIds(0).empty());
      ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(0);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        ASSERT_EQ("MapCollection_ItemAdded", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(2, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(0);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        expectedIds.insert(3);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(3).empty());
        ASSERT_EQ("MapCollection_ItemAdded", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(3, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Add(3);
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
        ASSERT_EQ("MapCollection_ItemAdded", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(4, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
    }

    TEST(MapCollectionTest, Remove) {
      MapCollection mapCollection;
      mapCollection.Add(0); // 2
      mapCollection.Add(0); // 3
      mapCollection.Add(3); // 4
      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Remove(4);
        std::set<int> expectedIds;
        expectedIds.insert(2);
        expectedIds.insert(3);
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(0));
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(2).empty());
        expectedIds.clear();
        ASSERT_TRUE(expectedIds == mapCollection.GetChildIds(3));
        ASSERT_EQ(0u, mapCollection.nodes.count(4));
        ASSERT_EQ("MapCollection_ItemRemoved", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(4, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
    }

    TEST(MapCollectionTest, RemoveChildren) {
      MapCollection mapCollection;
      mapCollection.Add(0); // 2
      mapCollection.Add(2); // 3
      mapCollection.Add(3); // 4
      mapCollection.Add(4); // 5
      {
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        mapCollection.Remove(2);
        ASSERT_TRUE(mapCollection.GetChildIds(0).empty());
        ASSERT_TRUE(mapCollection.GetChildIds(1).empty());
        ASSERT_EQ(0u, mapCollection.nodes.count(2));
        ASSERT_EQ(0u, mapCollection.nodes.count(3));
        ASSERT_EQ(0u, mapCollection.nodes.count(4));
        ASSERT_EQ("MapCollection_ItemRemoved", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(2, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
    }

    TEST(MapCollectionTest, GetMap) {
      MapCollection mapCollection;
      mapCollection.Add(0); // 2
      mapCollection.Add(0); // 3
      mapCollection.Add(3); // 4
      ASSERT_EQ(&mapCollection.GetMap(2), &mapCollection.GetMap(2));
      ASSERT_NE(&mapCollection.GetMap(2), &mapCollection.GetMap(3));
      ASSERT_NE(&mapCollection.GetMap(2), &mapCollection.GetMap(4));
      ASSERT_NE(&mapCollection.GetMap(3), &mapCollection.GetMap(2));
      ASSERT_EQ(&mapCollection.GetMap(3), &mapCollection.GetMap(3));
      ASSERT_NE(&mapCollection.GetMap(3), &mapCollection.GetMap(4));
      ASSERT_NE(&mapCollection.GetMap(4), &mapCollection.GetMap(2));
      ASSERT_NE(&mapCollection.GetMap(4), &mapCollection.GetMap(3));
      ASSERT_EQ(&mapCollection.GetMap(4), &mapCollection.GetMap(4));
    }

    TEST(MapCollectionTest, NameUpdated) {
      MapCollection mapCollection;
      mapCollection.Add(0); // 2
      mapCollection.Add(0); // 3
      {
        Map& map = mapCollection.GetMap(2);
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        map.SetName("foo");
        ASSERT_EQ("MapCollection_ItemNameUpdated", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(2, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
      {
        Map& map = mapCollection.GetMap(3);
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        map.SetName("bar");
        ASSERT_EQ("MapCollection_ItemNameUpdated", observer.calledHandler);
        ASSERT_EQ(&mapCollection, observer.mapCollectionValues["mapCollection"]);
        ASSERT_EQ(3, observer.intValues["id"]);
        mapCollection.RemoveObserver(observer);
      }
      {
        Map& map = mapCollection.GetMap(2);
        MockMapCollectionObserver observer;
        mapCollection.AddObserver(observer);
        map.SetName("foo");
        ASSERT_EQ("", observer.calledHandler);
        mapCollection.RemoveObserver(observer);
      }
    }

  }
}

#endif
