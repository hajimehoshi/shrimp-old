#include "Shrimp/Presenters/MapTreeViewPresenter.h"
#include "Shrimp/Util/Uncopyable.h"

#ifdef __TEST

#include <map>
#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : private Util::Uncopyable {
    public:
      void AddItem(int id, int parentId, const std::string& text) {
        this->calledMethod = "AddItem";
        this->intValues["id"] = id;
        this->intValues["parentId"] = parentId;
        this->stringValues["text"] = text;
      }
      void RemoveItem(int id) {
        this->calledMethod = "RemoveItem";
        this->intValues["id"] = id;
      }
      void Reset(const Models::MapCollection& mapCollection) {
        this->calledMethod = "Reset";
        this->mapCollectionValues["mapCollection"] = &mapCollection;
      }
      void SetPresenter(MapTreeViewPresenter<MockMapTreeView>&) {
      }
      void UpdateItem(int id, const std::string& text) {
        this->calledMethod = "UpdateItem";
        this->intValues["id"] = id;
        this->stringValues["text"] = text;
      }
      std::string calledMethod;
      std::map<std::string, int> intValues;
      std::map<std::string, std::string> stringValues;
      std::map<std::string, const Models::MapCollection*> mapCollectionValues;
    };

    TEST(MapTreeViewPresenterTest, Reset) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      ASSERT_EQ("Reset", view.calledMethod);
      ASSERT_EQ(&mapCollection, view.mapCollectionValues["mapCollection"]);
    }

    TEST(MapTreeViewPresenterTest, AddItem) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      {
        presenter.MapTreeView_ItemAdded(view, 0);
        const Models::MapCollection::ChildIds& childIds =
          mapCollection.GetChildIds(0);
        ASSERT_EQ(1u, childIds.size());
        ASSERT_EQ("AddItem", view.calledMethod);
        int newChildId = *(childIds.begin());
        ASSERT_EQ(newChildId, view.intValues["id"]);
        ASSERT_EQ(0, view.intValues["parentId"]);
        ASSERT_EQ("", view.stringValues["name"]);
      }
      {
        presenter.MapTreeView_ItemAdded(view, 2);
        const Models::MapCollection::ChildIds& childIds =
          mapCollection.GetChildIds(2);
        ASSERT_EQ(1u, childIds.size());
        ASSERT_EQ("AddItem", view.calledMethod);
        int newChildId = *(childIds.begin());
        ASSERT_EQ(newChildId, view.intValues["id"]);
        ASSERT_EQ(2, view.intValues["parentId"]);
        ASSERT_EQ("", view.stringValues["name"]);
      }
    }

    TEST(MapTreeViewPresenterTest, RemoveItem) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      presenter.MapTreeView_ItemAdded(view, 0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());      
      presenter.MapTreeView_ItemRemoved(view, newChildId);
      ASSERT_EQ("RemoveItem", view.calledMethod);
      ASSERT_EQ(newChildId, view.intValues["id"]);
    }

    TEST(MapTreeViewPresenterTest, UpdateItem) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      presenter.MapTreeView_ItemAdded(view, 0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());
      Models::Map& map = mapCollection.GetMap(newChildId);
      presenter.MapTreeView_ItemUpdated(view, newChildId, "foo");
      ASSERT_EQ("foo", map.GetName());
      ASSERT_EQ("UpdateItem", view.calledMethod);
      ASSERT_EQ("foo", view.stringValues["text"]);
      presenter.MapTreeView_ItemUpdated(view, newChildId, "bar");
      ASSERT_EQ("bar", map.GetName());
      ASSERT_EQ("UpdateItem", view.calledMethod);
      ASSERT_EQ("bar", view.stringValues["text"]);
    }

  }
}

#endif
