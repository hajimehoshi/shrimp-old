#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    typedef Util::ObserverContainer<IMapObserver*>::Observers Observers;

    Map::Map(const std::string& name, int width, int height)
      : name(name), width(width), height(height) {
      assert(0 < this->width);
      assert(0 < this->height);
      for (int i = 0; i < LayerCount; ++i) {
        this->layers[i] = new Tile[this->width * this->height];
      }
    }

    Map::~Map() {
      for (int i = 0; i < LayerCount; ++i) {
        delete[] this->layers[i];
      }
    }

    void Map::SetHeight(int height) {
      assert(0 < height);
      if (this->height != height) {
        this->height = height;
        const Observers& e = this->observers.GetObservers();
        for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
          (*it)->OnHeightUpdated();
        }
      }
    }

    void Map::SetName(const std::string& name) {
      if (this->name != name) {
        this->name = name;
        const Observers& e = this->observers.GetObservers();
        for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
          (*it)->OnNameUpdated();
        }
      }
    }

    void Map::SetTile(int layer, int x, int y, const Tile& tile) {
      assert(0 <= layer);
      assert(layer < LayerCount);
      assert(0 <= x);
      assert(x < this->width);
      assert(0 <= y);
      assert(y < this->height);
      if (this->layers[layer][x + y * this->width] != tile) {
        this->layers[layer][x + y * this->width] = tile;
        const Observers& e = this->observers.GetObservers();
        for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
          (*it)->OnTileUpdated();
        }
      }
    }

    void Map::SetWidth(int width) {
      assert(0 < width);
      if (this->width != width) {
        this->width = width;
        const Observers& e = this->observers.GetObservers();
        for (Observers::const_iterator it = e.begin(); it != e.end(); ++it) {
          (*it)->OnWidthUpdated();
        }
      }
    }

    IMapObserver::~IMapObserver() {
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    class MockMapObserver : public IMapObserver {
    public:
      MockMapObserver() {
        this->Clear();
      }
      virtual ~MockMapObserver() { }
      void Clear() {
        this->IsCalledOnHeightUpdated = false;
        this->IsCalledOnNameUpdated = false;
        this->IsCalledOnTileUpdated = false;
        this->IsCalledOnWidthUpdated = false;
      }
      virtual void OnHeightUpdated() {
        this->IsCalledOnHeightUpdated = true;
      }
      bool IsCalledOnHeightUpdated;
      virtual void OnNameUpdated() {
        this->IsCalledOnNameUpdated = true;
      }
      bool IsCalledOnNameUpdated;
      virtual void OnTileUpdated() {
        this->IsCalledOnTileUpdated = true;
      }
      bool IsCalledOnTileUpdated;
      virtual void OnWidthUpdated() {
        this->IsCalledOnWidthUpdated = true;
      }
      bool IsCalledOnWidthUpdated;
    };

    TEST(MapTest, Name) {
      Map map("Foo", 20, 15);
      MockMapObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ("Foo", map.GetName());

      observer.Clear();
      map.SetName("Foo");
      ASSERT_EQ("Foo", map.GetName());
      ASSERT_FALSE(observer.IsCalledOnNameUpdated);

      observer.Clear();
      map.SetName("Bar");
      ASSERT_EQ("Bar", map.GetName());
      ASSERT_TRUE(observer.IsCalledOnNameUpdated);
    }

    TEST(MapTest, Width) {
      Map map("Foo", 20, 15);
      MockMapObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ(20, map.GetWidth());

      observer.Clear();
      map.SetWidth(20);
      ASSERT_EQ(20, map.GetWidth());
      ASSERT_FALSE(observer.IsCalledOnWidthUpdated);

      observer.Clear();
      map.SetWidth(21);
      ASSERT_EQ(21, map.GetWidth());
      ASSERT_TRUE(observer.IsCalledOnWidthUpdated);
    }

    TEST(MapTest, Height) {
      Map map("Foo", 20, 15);
      MockMapObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ(15, map.GetHeight());

      observer.Clear();
      map.SetHeight(15);
      ASSERT_EQ(15, map.GetHeight());
      ASSERT_FALSE(observer.IsCalledOnHeightUpdated);

      observer.Clear();
      map.SetHeight(16);
      ASSERT_EQ(16, map.GetHeight());
      ASSERT_TRUE(observer.IsCalledOnHeightUpdated);
    }

    TEST(MapTest, Tile) {
      Map map("Foo", 20, 15);
      MockMapObserver observer;
      map.AddObserver(observer);

      ASSERT_TRUE(Tile(0, 0) == map.GetTile(0, 1, 2));

      observer.Clear();
      map.SetTile(0, 1, 2, Tile(0, 0));
      ASSERT_TRUE(Tile(0, 0) == map.GetTile(0, 1, 2));
      ASSERT_FALSE(observer.IsCalledOnTileUpdated);

      observer.Clear();
      map.SetTile(0, 1, 2, Tile(3, 4));
      ASSERT_TRUE(Tile(3, 4) == map.GetTile(0, 1, 2));
      ASSERT_TRUE(observer.IsCalledOnTileUpdated);
    }

  }
}

#endif
