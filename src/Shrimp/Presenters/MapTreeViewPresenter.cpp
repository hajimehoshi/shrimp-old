#include "Shrimp/Presenters/MapTreeViewPresenter.h"

namespace Shrimp {
  namespace Presenters {

    MapTreeViewPresenter::MapTreeViewPresenter(IMapTreeView& view,
                                               Models::MapCollection& mapCollection)
      : view(view), mapCollection(mapCollection) {
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
      MapTreeViewPresenter presenter(view, mapCollection);
      ASSERT_EQ(&view, &presenter.GetView());
      ASSERT_EQ(&mapCollection, &presenter.GetMapCollection());
    }

  }
}

#endif
