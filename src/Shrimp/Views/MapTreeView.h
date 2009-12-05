#ifndef SHRIMP_VIEWS_TREEVIEW_H
#define SHRIMP_VIEWS_TREEVIEW_H

#include <cassert>
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include "Shrimp/Presenters/MapTreeViewPresenter.h"
#include "Shrimp/Views/WndProc.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Views {

    class MapTreeView : private Util::Uncopyable {
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    private:
      typedef Presenters::MapTreeViewPresenter<MapTreeView> Presenter;
      static WNDCLASSEX wndClass;
      static WNDPROC defaultWndProc;
    public:
      MapTreeView(HWND parent);
      ~MapTreeView();
      void AddItem(int, std::string) { }
      void RemoveItem(int) { }
      inline void SetPresenter(Presenter& presenter) {
        assert(!this->presenter);
        this->presenter = &presenter;
      }
      void Show();
      void UpdateItem(int, std::string) { }
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
      Presenter* presenter;
    };

  }
}

#endif
