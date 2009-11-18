#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <map>
#include <list>
#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection {
    private:
      struct Node {
        static const int InvalidId = -1;
        int ParentId;
        Models::Map* Map;
        std::set<int> ChildIds;
        Node(int parentId, Models::Map* map);
      };
    public:
      MapCollection();
      ~MapCollection();
      void Add(int parentId, Map& map);
      inline void AddObserver(IMapCollectionObserver& observer) {
        this->Observers.insert(&observer);
      }
      const std::set<int>& GetChildIds(int id) const;
      Map& GetMap(int id) const;
      int GetProjectNodeId() const;
      int GetRecycleBinNodeId() const;
      inline void RemoveObserver(IMapCollectionObserver& observer) {
        std::set<IMapCollectionObserver*>::iterator it = this->Observers.find(&observer);
        assert(it != this->Observers.end());
        this->Observers.erase(it);
      }
    private:
      MapCollection(const MapCollection& mapCollection);
      MapCollection& operator=(const MapCollection& rhs);
      int GenerateNextId();
      Node* GetNode(int id) const;
      int NextId;
      std::map<int, Node*> Nodes;
      std::set<IMapCollectionObserver*> Observers;
      int ProjectNodeId;
      int RecycleBinNodeId;
    };

    class IMapCollectionObserver {
    public:
      IMapCollectionObserver() { }
      virtual ~IMapCollectionObserver() = 0;
      virtual void OnItemAdded() { }
    private:
      IMapCollectionObserver(const IMapCollectionObserver& mapObserver);
      IMapCollectionObserver& operator=(const IMapCollectionObserver& rhs);
    };

  }
}

#endif
