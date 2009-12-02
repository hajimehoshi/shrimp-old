#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    class IMapTreeView;

    class MapTreeViewPresenter : public Models::IMapCollectionObserver {
    public:
      MapTreeViewPresenter(Models::MapCollection& mapCollection);
      ~MapTreeViewPresenter();
      inline Models::MapCollection& GetMapCollection() const {
        return this->mapCollection;
      }
      inline IMapTreeView& GetView() const {
        assert(this->view);
        return *(this->view);
      }
      inline void SetView(IMapTreeView& view) {
        assert(!this->view);
        this->view = &view;
      }
      void OnItemAdded(int index);
      void OnItemRemoved(int index);
    private:
      Models::MapCollection& mapCollection;
      IMapTreeView* view;
    };

    class IMapTreeView {
    public:
      virtual ~IMapTreeView() { }
      virtual void Add() = 0;
      virtual void Remove() = 0;
    };

  }
}

#endif
