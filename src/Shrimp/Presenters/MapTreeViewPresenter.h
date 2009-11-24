#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    class IMapTreeView;

    class MapTreeViewPresenter {
    public:
      MapTreeViewPresenter(IMapTreeView& view,
                           Models::MapCollection& mapCollection);
      inline Models::MapCollection& GetMapCollection() {
        return this->mapCollection;
      }
      inline IMapTreeView& GetView() {
        return this->view;
      }
    private:
      IMapTreeView& view;
      Models::MapCollection& mapCollection;
    };

    class IMapTreeView {
    };

  }
}

#endif
