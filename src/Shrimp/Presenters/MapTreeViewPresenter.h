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
      void Add(int parentId);
      void MapCollection_OnItemAdded(int id);
      void MapCollection_OnItemRemoved(int id);
      void MapCollection_OnItemUpdated(int id);
      void Remove(int id);
      void Update(int id, std::string name);
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
      void MapTreeViewPresenter<TView>::Add(int parentId) {
      this->mapCollection.Add(parentId);
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
      void MapTreeViewPresenter<TView>::MapCollection_OnItemAdded(int id) {
      this->view.Add(id, "");
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_OnItemRemoved(int id) {
      this->view.Remove(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::MapCollection_OnItemUpdated(int id) {
      this->view.Update(id, this->mapCollection.GetMap(id).GetName());
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::Remove(int id) {
      this->mapCollection.Remove(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::Update(int id, std::string name) {
      this->mapCollection.GetMap(id).SetName(name);
    }

  }
}

#endif
