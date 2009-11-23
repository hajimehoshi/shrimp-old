#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <string>
#include "Shrimp/Models/Tile.h"
#include "Shrimp/Util/ObserverContainer.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Models {

    class IMapObserver;

    class Map : private Util::Uncopyable {
    public:
      static const int LayerCount = 2;
    public:
      Map(const std::string& name, int width, int height);
      ~Map();
      inline void AddObserver(IMapObserver& observer) {
        this->observers.Add(&observer);
      }
      inline int GetHeight() const {
        return this->height;
      }
      inline const std::string& GetName() const {
        return this->name;
      }
      inline const Tile& GetTile(int layer, int x, int y) const {
        return this->layers[layer][x + y * this->width];
      }
      inline int GetWidth() const {
        return this->width;
      }
      inline void RemoveObserver(IMapObserver& observer) {
        this->observers.Remove(&observer);
      }
      void SetHeight(int height);
      void SetName(const std::string& name);
      void SetTile(int layer, int x, int y, const Tile& tile);
      void SetWidth(int width);
    private:
      std::string name;
      int width;
      int height;
      Tile* layers[LayerCount];
      Util::ObserverContainer<IMapObserver*> observers;
    };

    class IMapObserver : private Util::Uncopyable {
    public:
      IMapObserver() { }
      virtual ~IMapObserver() = 0;
      virtual void OnHeightUpdated() = 0;
      virtual void OnNameUpdated() = 0;
      virtual void OnTileUpdated() = 0;
      virtual void OnWidthUpdated() = 0;
    };

  }
}

#endif
