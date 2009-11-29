#ifndef SHRIMP_VIEWS_TREEVIEW_H
#define SHRIMP_VIEWS_TREEVIEW_H

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Singleton.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class MapTreeView : private Util::Uncopyable {
    private:
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    public:
      MapTreeView(HWND parent);
      ~MapTreeView();
      void Show();
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
    };

    class MapTreeViewWC : public Util::Singleton<MapTreeViewWC> {
      friend class Util::Singleton<MapTreeViewWC>;
    public:
      inline const WNDCLASSEX& GetWndClass() const {
        return this->wndClass;
      }
      inline const WNDPROC GetDefaultWndProc() const {
        assert(this->defaultWndProc);
        return this->defaultWndProc;
      }
    private:
      MapTreeViewWC();
      WNDCLASSEX wndClass;
      WNDPROC defaultWndProc;
    };

  }
}

#endif
