#include "Shrimp/Presenters/MapTreeViewPresenter.h"

namespace Shrimp {
  namespace Presenters {

    MapTreeViewPresenter::MapTreeViewPresenter(IMapTreeView& view)
      : view(view), mapCollection(0) {
    }

    MapTreeViewPresenter::~MapTreeViewPresenter() {
    }

    void MapTreeViewPresenter::OnItemAdded(int index) {
    }

    void MapTreeViewPresenter::OnItemRemoved(int index) {
    }

    void MapTreeViewPresenter::SetMapCollection(Models::MapCollection& mapCollection) {
      if (this->mapCollection) {
        this->mapCollection->RemoveObserver(*this);
      }
      this->mapCollection = &mapCollection;
      if (this->mapCollection) {
        this->mapCollection->AddObserver(*this);
      }
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : public IMapTreeView {
    };

    TEST(MapTreeViewPresenterTest, Constractor) {
      IMapTreeView view;
      // Models::MapCollection mapCollection;
      MapTreeViewPresenter presenter(view);
      ASSERT_EQ(&view, &presenter.GetView());
      //ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
    }

  }
}

#endif
