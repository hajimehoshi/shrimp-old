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

    class MapTreeView : public Presenters::IMapTreeView {
    private:
      typedef Presenters::MapTreeViewPresenter Presenter;
      static WNDCLASSEX wndClass;
      static WNDPROC defaultWndProc;
      template<class T> friend
        LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    public:
      MapTreeView(HWND parent, Presenter& presenter);
      ~MapTreeView();
      void Add() { }
      void Remove() { }
      void Show();
    private:
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
      Presenter& presenter;
    };

  }
}

#endif
