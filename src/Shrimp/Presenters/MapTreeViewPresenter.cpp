#include "Shrimp/Presenters/MapTreeViewPresenter.h"

namespace Shrimp {
  namespace Presenters {

    MapTreeViewPresenter::MapTreeViewPresenter(Models::MapCollection& mapCollection,
                                               IMapTreeView& view)
      : mapCollection(mapCollection), view(view) {
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
    };

    TEST(MapTreeViewPresenterTest, Constractor) {
      IMapTreeView view;
      Models::MapCollection mapCollection;
      MapTreeViewPresenter presenter(mapCollection, view);
      ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
      ASSERT_EQ(&view, &presenter.GetView());
    }

  }
}

#endif
