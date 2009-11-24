#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

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
        for (Observers::const_iterator it = this->observers.begin();
             it != this->observers.end();
             ++it) {
          (*it)->OnHeightUpdated();
        }
      }
    }

    void Map::SetName(const std::string& name) {
      if (this->name != name) {
        this->name = name;
        for (Observers::const_iterator it = this->observers.begin();
             it != this->observers.end();
             ++it) {
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
        for (Observers::const_iterator it = this->observers.begin();
             it != this->observers.end();
             ++it) {
          (*it)->OnTileUpdated();
        }
      }
    }

    void Map::SetWidth(int width) {
      assert(0 < width);
      if (this->width != width) {
        this->width = width;
        for (Observers::const_iterator it = this->observers.begin();
             it != this->observers.end();
             ++it) {
          (*it)->OnWidthUpdated();
        }
      }
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    class MockMapObserver : public IMapObserver {
    public:
      virtual ~MockMapObserver() { }
      virtual void OnHeightUpdated() {
        this->calledHandler = "OnHeightUpdated";
      }
      virtual void OnNameUpdated() {
        this->calledHandler = "OnNameUpdated";
      }
      virtual void OnTileUpdated() {
        this->calledHandler = "OnTileUpdated";
      }
      virtual void OnWidthUpdated() {
        this->calledHandler = "OnWidthUpdated";
      }
      std::string calledHandler;
    };

    TEST(MapTest, Map) {
      Map map;
      ASSERT_EQ("", map.GetName());
      ASSERT_EQ(20, map.GetWidth());
      ASSERT_EQ(15, map.GetHeight());
    }

    TEST(MapTest, Name) {
      Map map("Foo", 20, 15);
      ASSERT_EQ("Foo", map.GetName());
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetName("Foo");
        ASSERT_EQ("Foo", map.GetName());
        ASSERT_TRUE(observer.calledHandler.empty());
        map.RemoveObserver(observer);
      }
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetName("Bar");
        ASSERT_EQ("Bar", map.GetName());
        ASSERT_EQ("OnNameUpdated", observer.calledHandler);
        map.RemoveObserver(observer);
      }
    }

    TEST(MapTest, Width) {
      Map map("Foo", 20, 15);
      ASSERT_EQ(20, map.GetWidth());
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetWidth(20);
        ASSERT_EQ(20, map.GetWidth());
        ASSERT_TRUE(observer.calledHandler.empty());
        map.RemoveObserver(observer);
      }
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetWidth(21);
        ASSERT_EQ(21, map.GetWidth());
        ASSERT_EQ("OnWidthUpdated", observer.calledHandler);
        map.RemoveObserver(observer);
      }
    }

    TEST(MapTest, Height) {
      Map map("Foo", 20, 15);
      ASSERT_EQ(15, map.GetHeight());
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetHeight(15);
        ASSERT_EQ(15, map.GetHeight());
        ASSERT_TRUE(observer.calledHandler.empty());
        map.RemoveObserver(observer);
      }
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetHeight(16);
        ASSERT_EQ(16, map.GetHeight());
        ASSERT_EQ("OnHeightUpdated", observer.calledHandler);
        map.RemoveObserver(observer);
      }
    }

    TEST(MapTest, Tile) {
      Map map("Foo", 20, 15);
      ASSERT_TRUE(Tile(0, 0) == map.GetTile(0, 1, 2));
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetTile(0, 1, 2, Tile(0, 0));
        ASSERT_TRUE(Tile(0, 0) == map.GetTile(0, 1, 2));
        ASSERT_TRUE(observer.calledHandler.empty());
        map.RemoveObserver(observer);
      }
      {
        MockMapObserver observer;
        map.AddObserver(observer);
        map.SetTile(0, 1, 2, Tile(3, 4));
        ASSERT_TRUE(Tile(3, 4) == map.GetTile(0, 1, 2));
        ASSERT_EQ("OnTileUpdated", observer.calledHandler);
        map.RemoveObserver(observer);
      }
    }

  }
}

#endif
