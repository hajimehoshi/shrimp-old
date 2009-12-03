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
      void Add(int parentId);
      inline void SetView(IMapTreeView& view) {
        assert(!this->view);
        this->view = &view;
      }
      void OnItemAdded(int id);
      void OnItemRemoved(int id);
      void OnItemUpdated(int id);
      void Remove(int id);
      void Update(int id, std::string name);
    private:
      Models::MapCollection& mapCollection;
      IMapTreeView* view;
    };

    class IMapTreeView : private Util::Uncopyable {
    public:
      virtual ~IMapTreeView() { }
      virtual void Add(int id, std::string text) = 0;
      virtual void Remove(int id) = 0;
      virtual void Update(int id, std::string text) = 0;
    };

  }
}

#endif
