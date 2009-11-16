#ifndef SHRIMP_MODELS_MAPCOLLECTION_H
#define SHRIMP_MODELS_MAPCOLLECTION_H

#include <vector>
#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    class IMapCollectionObserver;

    class MapCollection {
    public:
      MapCollection();
      void Add(Map& map);
      Map& GetMap(int index);
      const Map& GetMap(int index) const;
      int GetMapCount() const;
    private:
      MapCollection(const MapCollection& mapCollection);
      MapCollection& operator=(const MapCollection& mapCollection);
      std::vector<Map*> Maps;
    };

    class IMapCollectionObserver {
    };

  }
}

#endif
