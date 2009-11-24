#ifndef SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H
#define SHRIMP_PRESENTERS_MAPTREEVIEWPRESENTER_H

namespace Shrimp {
  namespace Presenters {

    class IMapTreeView;

    class MapTreeViewPresenter {
    public:
      MapTreeViewPresenter(IMapTreeView& view);
      inline IMapTreeView& GetView() {
        return this->view;
      }
    private:
      IMapTreeView& view;
    };

    class IMapTreeView {
    };

  }
}

#endif
