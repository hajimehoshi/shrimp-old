#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <map>
#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection {
    public:
      enum NodeType {
        NodeTypeMap,
        NodeTypeRecycleBin,
        NodeTypeProject,
      };
    private:
      struct Node {
        int Id;
        int ParentId;
        MapCollection::NodeType NodeType;
        Models::Map* Map;
        Node(int id,
             int parentId,
             MapCollection::NodeType nodeType,
             Models::Map* map);
      };
    public:
      MapCollection();
      ~MapCollection();
      MapCollection::NodeType GetNodeType(int id) const;
      int GetRootNodeCount() const;
      void GetRootNodeIds(int* rootNodeIds) const;
    private:
      MapCollection(const MapCollection& mapCollection);
      MapCollection& operator=(const MapCollection& rhs);
      int GenerateNextId();
      int NextId;
      std::map<int, Node*> Nodes;
      int RootNodeIds[2];
    };

    class IMapCollectionObserver {
    };

  }
}

#endif
