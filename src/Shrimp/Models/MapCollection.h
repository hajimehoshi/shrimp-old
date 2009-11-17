#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <map>
#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection {
    private:
      struct Node {
        int Id;
        int ParentId;
        Models::Map* Map;
        Node(int id,
             int parentId,
             Models::Map* map);
      };
    public:
      MapCollection();
      ~MapCollection();
      void Add(int parentId, Map* const map);
      int GetChildNodeCount(int id) const;
      int GetProjectNodeId() const;
      int GetRecycleBinNodeId() const;
    private:
      MapCollection(const MapCollection& mapCollection);
      MapCollection& operator=(const MapCollection& rhs);
      int GenerateNextId();
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
