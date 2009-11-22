#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <map>
#include <set>
#include "Shrimp/Models/Map.h"
#include "Shrimp/Util/ObserverContainer.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection : private Util::Uncopyable {
    private:
      struct Node {
      public:
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
        this->observers.Add(&observer);
      }
      const std::set<int>& GetChildIds(int id) const;
      Map& GetMap(int id) const;
      int GetProjectNodeId() const;
      int GetRecycleBinNodeId() const;
      inline void RemoveObserver(IMapCollectionObserver& observer) {
        this->observers.Remove(&observer);
      }
    private:
      int GenerateNextId();
      Node* GetNode(int id) const;
      int nextId;
      std::map<int, Node*> nodes;
      Util::ObserverContainer<IMapCollectionObserver*> observers;
      int projectNodeId;
      int recycleBinNodeId;
    };

    class IMapCollectionObserver : private Util::Uncopyable {
    public:
      IMapCollectionObserver() { }
      virtual ~IMapCollectionObserver() = 0;
      virtual void OnItemAdded(int index) = 0;
    };

  }
}

#endif
