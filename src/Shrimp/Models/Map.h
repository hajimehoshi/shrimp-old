#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <set>
#include <string>
#include "Shrimp/Models/Tile.h"
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
        this->Observers.insert(&observer);
      }
      inline int GetHeight() const {
        return this->Height;
      }
      inline const std::string& GetName() const {
        return this->Name;
      }
      inline const Tile& GetTile(int layer, int x, int y) const {
        return this->Layers[layer][x + y * this->Width];
      }
      inline int GetWidth() const {
        return this->Width;
      }
      inline void RemoveObserver(IMapObserver& observer) {
        std::set<IMapObserver*>::iterator it = this->Observers.find(&observer);
        assert(it != this->Observers.end());
        this->Observers.erase(it);
      }
      void SetHeight(int height);
      void SetName(const std::string& name);
      void SetTile(int layer, int x, int y, const Tile& tile);
      void SetWidth(int width);
    private:
      std::string Name;
      int Width;
      int Height;
      Tile* Layers[LayerCount];
      std::set<IMapObserver*> Observers;
    };

    class IMapObserver : private Util::Uncopyable {
    public:
      IMapObserver() { }
      virtual ~IMapObserver() = 0;
      virtual void OnHeightUpdated() { }
      virtual void OnNameUpdated() { }
      virtual void OnTileUpdated() { }
      virtual void OnWidthUpdated() { }
    };

  }
}

#endif
