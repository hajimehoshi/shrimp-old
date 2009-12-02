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
    }

    void MapTreeViewPresenter::OnItemAdded(int id) {
    }

    void MapTreeViewPresenter::OnItemRemoved(int id) {
    }

    void MapTreeViewPresenter::Remove(int id) {
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : public IMapTreeView {
    public:
      void Add() {
        this->calledMethod = "Add";
      }
      void Remove() {
        this->calledMethod = "Remove";
      }
      std::string calledMethod;
      std::map<std::string, int> intValues;
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
    }

  }
}

#endif
