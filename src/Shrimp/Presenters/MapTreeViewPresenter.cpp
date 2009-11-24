#include "Shrimp/Presenters/MapTreeViewPresenter.h"

namespace Shrimp {
  namespace Presenters {

    MapTreeViewPresenter::MapTreeViewPresenter(IMapTreeView& view)
      : view(view) {
    }

  }
}

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Presenters {

    class MockMapTreeView : public IMapTreeView {
    };

    TEST(MapTreeViewPresenterTest, View) {
      IMapTreeView view;
      MapTreeViewPresenter presenter(view);
      ASSERT_EQ(&view, &presenter.GetView());
    }

  }
}

#endif


