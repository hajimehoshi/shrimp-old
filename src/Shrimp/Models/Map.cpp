#include "Shrimp/Models/Map.h"

namespace Shrimp {
  namespace Models {

    Map::Map(std::string name, int width, int height)
      : Name(name), Width(width), Height(height) {
    }

    void Map::NotifyObservers(const std::string& property) {
      for (std::list<IObserver*>::iterator it = this->Observers.begin();
           it != this->Observers.end();
           ++it) {
        (*it)->Notify(property);
      }
    }

    void Map::SetHeight(int height) {
      if (this->Height != height) {
        this->Height = height;
        this->NotifyObservers("Height");
      }
    }

    void Map::SetName(const std::string& name) {
      if (this->Name != name) {
        this->Name = name;
        this->NotifyObservers("Name");
      }
    }

    void Map::SetWidth(int width) {
      if (this->Width != width) {
        this->Width = width;
        this->NotifyObservers("Width");
      }
    }

  }
}

#if __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Models {

    TEST(Map, Name) {
      Map map("Foo", 20, 15);
      MockObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ("Foo", map.GetName());

      observer.Clear();
      map.SetName("Foo");
      ASSERT_EQ("Foo", map.GetName());
      ASSERT_TRUE(observer.GetLastNotifiedProperty().empty());

      observer.Clear();
      map.SetName("Bar");
      ASSERT_EQ("Bar", map.GetName());
      ASSERT_EQ("Name", observer.GetLastNotifiedProperty());
    }

    TEST(Map, Width) {
      Map map("Foo", 20, 15);
      MockObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ(20, map.GetWidth());

      observer.Clear();
      map.SetWidth(20);
      ASSERT_EQ(20, map.GetWidth());
      ASSERT_TRUE(observer.GetLastNotifiedProperty().empty());

      observer.Clear();
      map.SetWidth(21);
      ASSERT_EQ(21, map.GetWidth());
      ASSERT_EQ("Width", observer.GetLastNotifiedProperty());
    }

    TEST(Map, Height) {
      Map map("Foo", 20, 15);
      MockObserver observer;
      map.AddObserver(observer);

      ASSERT_EQ(15, map.GetHeight());

      observer.Clear();
      map.SetHeight(15);
      ASSERT_EQ(15, map.GetHeight());
      ASSERT_TRUE(observer.GetLastNotifiedProperty().empty());

      observer.Clear();
      map.SetHeight(16);
      ASSERT_EQ(16, map.GetHeight());
      ASSERT_EQ("Height", observer.GetLastNotifiedProperty());
    }

  }

}

#endif
