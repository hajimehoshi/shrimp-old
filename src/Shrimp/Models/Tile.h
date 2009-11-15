#ifndef SHRIMP_MODELS_TILE
#define SHRIMP_MODELS_TILE

#include <stdint.h>

namespace Shrimp {
  namespace Models {

    class Tile {
    public:
      Tile()
        : TileSetId(0), TileId(0) {
      }
      Tile(int16_t tileSetId, int16_t tileId)
        : TileSetId(tileSetId), TileId(tileId) {
      }
      Tile(const Tile& tile)
        : TileSetId(tile.TileSetId), TileId(tile.TileId) {
      }
      Tile& operator=(const Tile& rhs) {
        this->TileSetId = rhs.TileSetId;
        this->TileId    = rhs.TileId;
        return *this;
      }
      inline bool operator==(const Tile& rhs) const {
        return (this->TileSetId == rhs.TileSetId &&
                this->TileId == rhs.TileId);
      }
      inline bool operator!=(const Tile& rhs) const {
        return !(*this == rhs);
      }
      inline int16_t GetTileId() const {
        return this->TileId;
      }
      inline int16_t GetTileSetId() const {
        return this->TileSetId;
      }
      inline void SetTileId(int16_t tileId) {
        this->TileId = tileId;
      }
      inline void SetTileSetId(int16_t tileSetId) {
        this->TileSetId = tileSetId;
      }
    private:
      int16_t TileSetId;
      int16_t TileId;
    };

  }
}

#endif
