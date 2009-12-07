#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <string>
#include "Shrimp/Models/Tile.h"
#include "Shrimp/Util/Observers.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Models {

    class IMapObserver;

    class Map : private Util::Uncopyable {
    private:
      typedef Util::Observers<IMapObserver*> Observers;
    public:
      static const int LayerCount = 2;
    public:
      Map(int id, const std::string& name = "", int width = 20, int height = 15);
      ~Map() throw();
      inline void AddObserver(IMapObserver& observer) {
        this->observers.Add(&observer);
      }
      inline int GetHeight() const {
        return this->height;
      }
      inline int GetId() const {
        return this->id;
      }
      inline const std::string& GetName() const {
        return this->name;
      }
      inline const Tile& GetTile(int layer, int x, int y) const {
        assert(0 <= layer);
        assert(layer < LayerCount);
        assert(0 <= x);
        assert(x < this->width);
        assert(0 <= y);
        assert(y < this->height);
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
      Map(int id, const std::string&, int width);
      const int id;
      std::string name;
      int width;
      int height;
      Tile* layers[LayerCount];
      Observers observers;
    };

    class IMapObserver : private Util::Uncopyable {
    public:
      virtual ~IMapObserver() throw() { }
      virtual void Map_HeightUpdated(Map& map) = 0;
      virtual void Map_NameUpdated(Map& map) = 0;
      virtual void Map_TileUpdated(Map& map) = 0;
      virtual void Map_WidthUpdated(Map& map) = 0;
    };

  }
}

#endif
