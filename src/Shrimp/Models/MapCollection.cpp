#include <cassert>
#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Models {

    typedef Util::ObserverContainer<IMapCollectionObserver*>::Observers Observers;

    MapCollection::Node::Node(int parentId)
      : parentId(parentId) {
    }

    MapCollection::MapCollection()
      : nextId(0) {
      int id;
      Node* node;

      id = this->GenerateNextId();
      assert(id == 0);
      node = new Node(Node::InvalidId);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->projectNodeId = id;

      id = this->GenerateNextId();
      assert(id == 1);
      node = new Node(Node::InvalidId);
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

    void MapCollection::Add(int parentId) {
      int id = this->GenerateNextId();
      Node* node = new Node(parentId);
      this->nodes.insert(std::map<int, Node*>::value_type(id, node));
      this->GetNode(parentId)->childIds.insert(id);
      const Observers& e = this->observers.GetObservers();
      for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
        (*it)->OnItemAdded(id);
      }
    }

    const MapCollection::ChildIds& MapCollection::GetChildIds(int id) const {
      return this->GetNode(id)->childIds;
    }

    Map& MapCollection::GetMap(int id) const {
      return this->GetNode(id)->map;
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

    void MapCollection::Remove(int id) {
      Node* node = this->GetNode(id);
      Node* parentNode = this->GetNode(node->parentId);
      std::set<int>::iterator it = parentNode->childIds.find(id);
      assert(it != parentNode->childIds.end());
      parentNode->childIds.erase(it);
      this->RemoveNode(id);
      const Observers& e = this->observers.GetObservers();
      for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
        (*it)->OnItemRemoved(id);
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
      virtual ~MockMapCollectionObserver() { }
      virtual void OnItemAdded(int index) {
        this->calledHandler = "OnItemAdded";
        this->intValues["index"] = index;
      }
      virtual void OnItemRemoved(int index) {
        this->calledHandler = "OnItemRemoved";
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
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(2, observer.intValues["index"]);
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
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(3, observer.intValues["index"]);
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
        ASSERT_EQ("OnItemAdded", observer.calledHandler);
        ASSERT_EQ(4, observer.intValues["index"]);
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
        ASSERT_EQ("OnItemRemoved", observer.calledHandler);
        ASSERT_EQ(4, observer.intValues["index"]);
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
        ASSERT_EQ("OnItemRemoved", observer.calledHandler);
        ASSERT_EQ(2, observer.intValues["index"]);
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

  }
}

#endif
