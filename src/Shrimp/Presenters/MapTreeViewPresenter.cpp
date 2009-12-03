#include <map>
#include "Shrimp/Presenters/MapTreeViewPresenter.h"

namespace Shrimp {
  namespace Presenters {

    MapTreeViewPresenter::MapTreeViewPresenter(Models::MapCollection& mapCollection)
      : mapCollection(mapCollection), view(0) {
      this->mapCollection.AddObserver(*this);
    }

    MapTreeViewPresenter::~MapTreeViewPresenter() {
      this->mapCollection.RemoveObserver(*this);
    }

    void MapTreeViewPresenter::Add(int parentId) {
      this->mapCollection.Add(parentId);
    }

    void MapTreeViewPresenter::OnItemAdded(int id) {
      assert(this->view);
      this->view->Add(id, "");
    }

    void MapTreeViewPresenter::OnItemRemoved(int id) {
      assert(this->view);
      this->view->Remove(id);
    }

    void MapTreeViewPresenter::OnItemUpdated(int id) {
      assert(this->view);
      this->view->Update(id, this->mapCollection.GetMap(id).GetName());
    }

    void MapTreeViewPresenter::Remove(int id) {
      this->mapCollection.Remove(id);
    }

    void MapTreeViewPresenter::Update(int id, std::string name) {
      this->mapCollection.GetMap(id).SetName(name);
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : public IMapTreeView {
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
      MapTreeViewPresenter presenter(mapCollection);
      ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
      MockMapTreeView view;
      presenter.SetView(view);
      ASSERT_EQ(&view, &presenter.GetView());
    }

    TEST(MapTreeViewPresenterTest, Add) {
      Models::MapCollection mapCollection;
      MapTreeViewPresenter presenter(mapCollection);
      MockMapTreeView view;
      presenter.SetView(view);
      presenter.Add(0);
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
      MapTreeViewPresenter presenter(mapCollection);
      MockMapTreeView view;
      presenter.SetView(view);
      presenter.Add(0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());      
      presenter.Remove(newChildId);
      ASSERT_EQ("Remove", view.calledMethod);
      ASSERT_EQ(newChildId, view.intValues["id"]);
    }

    TEST(MapTreeViewPresenterTest, Update) {
      /*Models::MapCollection mapCollection;
      MapTreeViewPresenter presenter(mapCollection);
      MockMapTreeView view;
      presenter.SetView(view);
      presenter.Add(0);
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(0);
      int newChildId = *(childIds.begin());
      Models::Map& map = mapCollection.GetMap(newChildId);
      presenter.Update(newChildId, "foo");
      ASSERT_EQ("foo", map.GetName());
      ASSERT_EQ("Update", view.calledMethod);
      ASSERT_EQ("foo", view.stringValues["text"]);
      presenter.Update(newChildId, "bar");
      ASSERT_EQ("bar", map.GetName());
      ASSERT_EQ("Update", view.calledMethod);
      ASSERT_EQ("bar", view.stringValues["text"]);*/
    }

  }
}

#endif
