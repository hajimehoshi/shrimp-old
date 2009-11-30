#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    class IMapTreeView;

    class MapTreeViewPresenter : public Models::IMapCollectionObserver {
    public:
      MapTreeViewPresenter(IMapTreeView& view);
      ~MapTreeViewPresenter();
      inline Models::MapCollection& GetMapCollection() {
        return *(this->mapCollection);
      }
      inline IMapTreeView& GetView() {
        return this->view;
      }
      void SetMapCollection(Models::MapCollection& mapCollection);
      void OnItemAdded(int index);
      void OnItemRemoved(int index);
    private:
      IMapTreeView& view;
      Models::MapCollection* mapCollection;
    };

    class IMapTreeView {
    };

  }
}

#endif
