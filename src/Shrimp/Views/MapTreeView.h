#ifndef SHRIMP_VIEWS_TREEVIEW_H
#define SHRIMP_VIEWS_TREEVIEW_H

#include <cassert>
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <map>
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
      typedef std::map<int, HTREEITEM> TreeItems;
      static WNDCLASSEX wndClass;
      static WNDPROC defaultWndProc;
    public:
      MapTreeView(HWND parent);
      ~MapTreeView() throw();
      void AddItem(int id, int parentId, const std::string& text);
      void AddItemAsRoot(int id, const std::string& text);
      void Clear();
      void RemoveItem(int id);
      void Reset(const Models::MapCollection& mapCollection);
      inline void SetPresenter(Presenter& presenter) {
        assert(!this->presenter);
        this->presenter = &presenter;
      }
      template<class TItems>
        void ResetItems(const TItems& items);
      void Show();
      void UpdateItem(int, const std::string&) { }
    private:
      void AddItem(int id, HTREEITEM parent, const std::string& text);
      void RemoveTreeItem(int id);
      HTREEITEM GetTreeItem(int id);
      LRESULT ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam);
      HWND handle;
      Presenter* presenter;
      TreeItems treeItems;
    };

  }
}

#endif
