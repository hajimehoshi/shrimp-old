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
      void MapCollection_ItemAdded(int id);
      void MapCollection_ItemNameUpdated(int id);
      void MapCollection_ItemRemoved(int id);
      void MapTreeView_ItemAdded(int parentId);
      void MapTreeView_ItemRemoved(int id);
      void MapTreeView_ItemUpdated(int id, std::string name);
    private:
      Models::MapCollection& mapCollection;
      TView& view;
    };

    template<class TView>
      MapTreeViewPresenter<TView>::MapTreeViewPresenter(Models::MapCollection& mapCollection, TView& view)
      : mapCollection(mapCollection), view(view) {
      this->mapCollection.AddObserver(*this);
      this->view.SetPresenter(*this);
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
      void MapTreeViewPresenter<TView>::MapCollection_ItemAdded(int id) {
      this->view.AddItem(id, "");
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_ItemNameUpdated(int id) {
      this->view.UpdateItem(id, this->mapCollection.GetMap(id).GetName());
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_ItemRemoved(int id) {
      this->view.RemoveItem(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemAdded(int parentId) {
      this->mapCollection.Add(parentId);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemRemoved(int id) {
      this->mapCollection.Remove(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapTreeView_ItemUpdated(int id, std::string name) {
      this->mapCollection.GetMap(id).SetName(name);
    }

  }
}

#endif
