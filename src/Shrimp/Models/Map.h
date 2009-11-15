#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <list>
#include <string>
#include "Shrimp/IObserver.h"
#include "Shrimp/Models/Tile.h"

namespace Shrimp {
  namespace Models {

    class Map {
    public:
      static const int LayerCount = 2;
    public:
      Map(const std::string& name, int width, int height);
      ~Map();
      inline void AddObserver(IObserver& observer) {
        this->Observers.push_back(&observer);
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
      inline void RemoveObserver(IObserver& observer) {
        this->Observers.remove(&observer);
      }
      void SetHeight(int height);
      void SetName(const std::string& name);
      void SetTile(int layer, int x, int y, const Tile& tile);
      void SetWidth(int width);
    private:
      Map(const Map& map);
      Map& operator=(const Map& rhs);
      void NotifyObservers(const std::string& name);
      std::string Name;
      int Width;
      int Height;
      Tile* Layers[LayerCount];
      std::list<IObserver*> Observers;
    };

  }
}

#endif
