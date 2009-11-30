#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    class IMapTreeView;

    class MapTreeViewPresenter : public Models::IMapCollectionObserver {
    public:
      MapTreeViewPresenter(Models::MapCollection& mapCollection,
                           IMapTreeView& view);
      ~MapTreeViewPresenter();
      inline Models::MapCollection& GetMapCollection() const {
        return this->mapCollection;
      }
      inline IMapTreeView& GetView() const {
        return this->view;
      }
      void OnItemAdded(int index);
      void OnItemRemoved(int index);
    private:
      Models::MapCollection& mapCollection;
      IMapTreeView& view;
    };

    class IMapTreeView {
    };

  }
}

#endif
