#include <map>
#include "Shrimp/Presenters/MapTreeViewPresenter.h"
#include "Shrimp/Util/Uncopyable.h"

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : private Util::Uncopyable {
    public:
      void Add(int id, std::string text) {
        this->calledMethod = "Add";
        this->intValues["id"] = id;
        this->stringValues["text"] = text;
      }
      void Remove(int id) {
        this->calledMethod = "Remove";
        this->intValues["id"] = id;
      }
      void SetPresenter(MapTreeViewPresenter<MockMapTreeView>& presenter) {
      }
      void Update(int id, std::string text) {
        this->calledMethod = "Update";
        this->intValues["id"] = id;
        this->stringValues["text"] = text;
      }
      std::string calledMethod;
      std::map<std::string, int> intValues;
      std::map<std::string, std::string> stringValues;
    };

    TEST(MapTreeViewPresenterTest, MapTreeViewPresenter) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
      ASSERT_EQ(&view, &presenter.GetView());
    }

    TEST(MapTreeViewPresenterTest, Add) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      presenter.MapTreeView_ItemAdded(0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      ASSERT_EQ(1u, childIds.size());
      ASSERT_EQ("Add", view.calledMethod);
      int newChildId = *(childIds.begin());
      ASSERT_EQ(newChildId, view.intValues["id"]);
      ASSERT_EQ("", view.stringValues["name"]);
    }

    TEST(MapTreeViewPresenterTest, Remove) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      presenter.MapTreeView_ItemAdded(0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());      
      presenter.MapTreeView_ItemRemoved(newChildId);
      ASSERT_EQ("Remove", view.calledMethod);
      ASSERT_EQ(newChildId, view.intValues["id"]);
    }

    TEST(MapTreeViewPresenterTest, Update) {
      Models::MapCollection mapCollection;
      MockMapTreeView view;
      MapTreeViewPresenter<MockMapTreeView> presenter(mapCollection, view);
      presenter.MapTreeView_ItemAdded(0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());
      Models::Map& map = mapCollection.GetMap(newChildId);
      presenter.MapTreeView_ItemUpdated(newChildId, "foo");
      ASSERT_EQ("foo", map.GetName());
      ASSERT_EQ("Update", view.calledMethod);
      ASSERT_EQ("foo", view.stringValues["text"]);
      presenter.MapTreeView_ItemUpdated(newChildId, "bar");
      ASSERT_EQ("bar", map.GetName());
      ASSERT_EQ("Update", view.calledMethod);
      ASSERT_EQ("bar", view.stringValues["text"]);
    }

  }
}

#endif
