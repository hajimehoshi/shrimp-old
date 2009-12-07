#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    template<class TView>
    class MapTreeViewPresenter : public Models::IMapCollectionObserver {
    public:
      MapTreeViewPresenter(Models::MapCollection& mapCollection,
                           TView& view);
      ~MapTreeViewPresenter();
      inline Models::MapCollection& GetMapCollection() const;
      inline TView& GetView() const;
      void MapCollection_ItemAdded(Models::MapCollection& mapCollection, int id);
      void MapCollection_ItemNameUpdated(Models::MapCollection& mapCollection, int id);
      void MapCollection_ItemRemoved(Models::MapCollection& mapCollection, int id);
      void MapTreeView_ItemAdded(TView& mapTreeView, int parentId);
      void MapTreeView_ItemRemoved(TView& mapTreeView, int id);
      void MapTreeView_ItemUpdated(TView& mapTreeView, int id, std::string name);
    private:
      Models::MapCollection& mapCollection;
      TView& view;
    };

    template<class TView>
      MapTreeViewPresenter<TView>::MapTreeViewPresenter(Models::MapCollection& mapCollection, TView& view)
      : mapCollection(mapCollection), view(view) {
      this->mapCollection.AddObserver(*this);
      this->view.SetPresenter(*this);
      this->view.Reset();
    }

    template<class TView>
      MapTreeViewPresenter<TView>::~MapTreeViewPresenter() {
      this->mapCollection.RemoveObserver(*this);
    }

    template<class TView>
      inline Models::MapCollection& MapTreeViewPresenter<TView>::GetMapCollection() const {
      return this->mapCollection;
    }

    template<class TView>
      inline TView& MapTreeViewPresenter<TView>::GetView() const {
      return this->view;
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_ItemAdded(Models::MapCollection&, int id) {
      int parentId = mapCollection.GetParentId(id);
      this->view.AddItem(id, parentId, "");
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_ItemNameUpdated(Models::MapCollection&, int id) {
      this->view.UpdateItem(id, this->mapCollection.GetMap(id).GetName());
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_ItemRemoved(Models::MapCollection&, int id) {
      this->view.RemoveItem(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemAdded(TView&, int parentId) {
      this->mapCollection.Add(parentId);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemRemoved(TView&, int id) {
      this->mapCollection.Remove(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemUpdated(TView&, int id, std::string name) {
      this->mapCollection.GetMap(id).SetName(name);
    }

  }
}

#endif
