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
      this->view->Add(id, "");
    }

    void MapTreeViewPresenter::OnItemRemoved(int id) {
      this->view->Remove(id);
    }

    void MapTreeViewPresenter::Remove(int id) {
      this->mapCollection.Remove(id);
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : public IMapTreeView {
    public:
      void Add(int id, std::string name) {
        this->calledMethod = "Add";
        this->intValues["id"] = id;
        this->stringValues["name"] = name;
      }
      void Remove(int id) {
        this->calledMethod = "Remove";
        this->intValues["id"] = id;
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

  }
}

#endif
