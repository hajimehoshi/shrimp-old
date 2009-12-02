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

    void MapTreeViewPresenter::OnItemAdded(int index) {
    }

    void MapTreeViewPresenter::OnItemRemoved(int index) {
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
      }
      void Remove() {
      }
    };

    TEST(MapTreeViewPresenterTest, Constractor) {
      Models::MapCollection mapCollection;
      MapTreeViewPresenter presenter(mapCollection);
      ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
      MockMapTreeView view;
      presenter.SetView(view);
      ASSERT_EQ(&view, &presenter.GetView());
    }

  }
}

#endif
