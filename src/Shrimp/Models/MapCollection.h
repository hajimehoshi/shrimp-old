#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <map>
#include <set>
#include "Shrimp/Models/Map.h"
#include "Shrimp/Util/Observers.h"
#include "Shrimp/Util/Uncopyable.h"

#ifdef __TEST
# include <gtest/gtest.h>
#endif

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection : public IMapObserver {
#ifdef __TEST
      FRIEND_TEST(MapCollectionTest, Remove);
      FRIEND_TEST(MapCollectionTest, RemoveChildren);
#endif
    public:
      typedef std::set<int> ChildIds;
    private:
      typedef Util::Observers<IMapCollectionObserver*> Observers;
    private:
      struct Node : private Util::Uncopyable {
      public:
        static const int InvalidId = -1;
      public:
        Node(int id, int parentId);
        Map map;
        const int parentId;
        ChildIds childIds;
      };
    public:
      MapCollection();
      ~MapCollection();
      void Add(int parentId);
      inline void AddObserver(IMapCollectionObserver& observer) {
        this->observers.Add(&observer);
      }
      const ChildIds& GetChildIds(int id) const;
      Map& GetMap(int id) const;
      int GetProjectNodeId() const;
      int GetRecycleBinNodeId() const;
      void Map_OnHeightUpdated(Map& map) { }
      void Map_OnNameUpdated(Map& map);
      void Map_OnTileUpdated(Map& map) { }
      void Map_OnWidthUpdated(Map& map) { }
      void Remove(int id);
      inline void RemoveObserver(IMapCollectionObserver& observer) {
        this->observers.Remove(&observer);
      }
    private:
      int GenerateNextId();
      Node* GetNode(int id) const;
      void RemoveNode(int id);
      int nextId;
      std::map<int, Node*> nodes;
      Observers observers;
      int projectNodeId;
      int recycleBinNodeId;
    };

    class IMapCollectionObserver : private Util::Uncopyable {
    public:
      virtual ~IMapCollectionObserver() { }
      virtual void MapCollection_OnItemAdded(int id) = 0;
      virtual void MapCollection_OnItemRemoved(int id) = 0;
      virtual void MapCollection_OnItemUpdated(int id) = 0;
    };

  }
}

#endif
