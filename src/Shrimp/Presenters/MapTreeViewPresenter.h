#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

#include "Shrimp/Models/MapCollection.h"

namespace Shrimp {
  namespace Presenters {

    template<class TView>
    class MapTreeViewPresenter : public Models::IMapCollectionObserver {
    public:
      MapTreeViewPresenter(Models::MapCollection& mapCollection);
      ~MapTreeViewPresenter();
      inline Models::MapCollection& GetMapCollection() const;
      inline TView& GetView() const;
      void Add(int parentId);
      inline void SetView(TView& view);
      void OnItemAdded(int id);
      void OnItemRemoved(int id);
      void OnItemUpdated(int id);
      void Remove(int id);
      void Update(int id, std::string name);
    private:
      Models::MapCollection& mapCollection;
      TView* view;
    };

    template<class TView>
      MapTreeViewPresenter<TView>::MapTreeViewPresenter(Models::MapCollection& mapCollection)
      : mapCollection(mapCollection), view(0) {
      this->mapCollection.AddObserver(*this);
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
      assert(this->view);
      return *(this->view);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::OnItemAdded(int id) {
      assert(this->view);
      this->view->Add(id, "");
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::OnItemRemoved(int id) {
      assert(this->view);
      this->view->Remove(id);
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::OnItemUpdated(int id) {
      assert(this->view);
      this->view->Update(id, this->mapCollection.GetMap(id).GetName());
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::Remove(int id) {
      this->mapCollection.Remove(id);
    }

    template<class TView>
      inline void MapTreeViewPresenter<TView>::SetView(TView& view) {
      assert(!this->view);
      this->view = &view;
    }

    template<class TView>
      void MapTreeViewPresenter<TView>::Update(int id, std::string name) {
      this->mapCollection.GetMap(id).SetName(name);
    }

  }
}

#endif
