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
      const std::set<int>& GetChildIds(int id) const;
      Map& GetMap(int id) const;
      int GetProjectNodeId() const;
      int GetRecycleBinNodeId() const;
    private:
      MapCollection(const MapCollection& mapCollection);
      MapCollection& operator=(const MapCollection& rhs);
      int GenerateNextId();
      Node* GetNode(int id) const;
      int NextId;
      std::map<int, Node*> Nodes;
      int ProjectNodeId;
      int RecycleBinNodeId;
    };

    class IMapCollectionObserver {
    };

  }
}

#endif
