#ifndef SHRIMP_VIEWS_TREEVIEW_H
#define SHRIMP_VIEWS_TREEVIEW_H

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
      MapTreeView(HWND parent, Presenter& presenter);
      ~MapTreeView();
      void Add(int id, std::string text) { }
      void Remove(int id) { }
      void Show();
      void Update(int id, std::string text) { }
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
      Presenter& presenter;
    };

  }
}

#endif
