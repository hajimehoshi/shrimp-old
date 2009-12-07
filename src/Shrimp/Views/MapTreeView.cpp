#include <cassert>
#include <cstdlib>
#include <vector>
#include "Shrimp/Util/WideCharArray.h"
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    WNDCLASSEX MapTreeView::wndClass;

    WNDPROC MapTreeView::defaultWndProc;

    MapTreeView::MapTreeView(HWND parent)
      : handle(0), presenter(0) {
      if (!defaultWndProc) {
        ::ZeroMemory(&wndClass, sizeof(wndClass));
        wndClass.cbSize = sizeof(wndClass);
        ::GetClassInfoEx(0, WC_TREEVIEW, &wndClass);
        this->defaultWndProc = wndClass.lpfnWndProc;
        wndClass.lpfnWndProc = &WndProc<MapTreeView>;
        wndClass.lpszClassName = _T("ShrimpMapTreeView");
        if (!::RegisterClassEx(&wndClass)) {
          std::abort();
        }
      }
      assert(defaultWndProc);
      ::CreateWindowEx(WS_EX_CLIENTEDGE,
                       wndClass.lpszClassName,
                       0,
                       WS_CHILD | WS_VISIBLE | TVS_FULLROWSELECT,
                       200, 200, 100, 100,
                       parent,
                       0,
                       GetModuleHandle(0),
                       this);
      // this->handle is set on processing WM_NCCREATE in WndProc
      assert(this->handle);
    }

    MapTreeView::~MapTreeView() throw() {
      ::DestroyWindow(this->handle);
    }

    void MapTreeView::AddChildItems(const Models::MapCollection& mapCollection,
                                    int id) {
      const Models::MapCollection::ChildIds& childIds =
        mapCollection.GetChildIds(id);
      for (Models::MapCollection::ChildIds::const_iterator it = childIds.begin();
           it != childIds.end();
           ++it) {
        const int childId = *it;
        const int parentId = mapCollection.GetParentId(childId);
        const Models::Map& map = mapCollection.GetMap(childId);
        this->AddItem(childId, parentId, map.GetName());
        this->AddChildItems(mapCollection, childId);
      }
    }

    void MapTreeView::AddItem(int id, int parentId, const std::string& text) {
      this->AddItem(id, this->GetTreeItem(parentId), text);
    }

    void MapTreeView::AddItem(int id, HTREEITEM parent, const std::string& text) {
      TV_INSERTSTRUCT tvInsertStruct;
      ::ZeroMemory(&tvInsertStruct, sizeof(tvInsertStruct));
      tvInsertStruct.hInsertAfter = TVI_LAST;
      tvInsertStruct.hParent = parent;
      tvInsertStruct.item.mask = TVIF_TEXT | TVIF_PARAM;
      Util::WideCharArray wText(text);
      tvInsertStruct.item.pszText = wText.GetPtr();
      tvInsertStruct.item.lParam = id;
      HTREEITEM treeItem = TreeView_InsertItem(this->handle, &tvInsertStruct);
      assert(this->treeItems.find(id) == this->treeItems.end());
      this->treeItems.insert(TreeItems::value_type(id, treeItem));
    }

    void MapTreeView::AddItemAsRoot(int id, const std::string& text) {
      this->AddItem(id, TVI_ROOT, text);
    }

    void MapTreeView::Clear() {
      TreeView_DeleteAllItems(this->handle);
      this->treeItems.clear();
    }

    HTREEITEM MapTreeView::GetTreeItem(int id) {
      TreeItems::iterator it = this->treeItems.find(id);
      assert(it != this->treeItems.end());
      return it->second;
    }

    void MapTreeView::RemoveItem(int id) {
      // Get HTREEITEM value before deleting nodes.
      HTREEITEM treeItem = this->GetTreeItem(id);
      this->RemoveTreeItem(id);
      TreeView_DeleteItem(this->handle, treeItem);
    }

    void MapTreeView::RemoveTreeItem(int id) {
      HTREEITEM treeItem = this->GetTreeItem(id);
      for (HTREEITEM t = TreeView_GetChild(this->handle, treeItem);
           t != 0;
           t = TreeView_GetNextSibling(this->handle, t)) {
        TVITEM tvItem;
        tvItem.hItem = t;
        tvItem.mask = TVIF_PARAM;
        TreeView_GetItem(this->handle, &tvItem);
        this->RemoveTreeItem(tvItem.lParam);
      }
      this->treeItems.erase(id);
    }

    void MapTreeView::Reset(const Models::MapCollection& mapCollection) {
      this->Clear();
      this->AddItemAsRoot(mapCollection.GetProjectNodeId(), "Project");
      this->AddChildItems(mapCollection, mapCollection.GetProjectNodeId());
      this->AddItemAsRoot(mapCollection.GetRecycleBinNodeId(), "Recycle Bin");
      this->AddChildItems(mapCollection, mapCollection.GetRecycleBinNodeId());
      
    }

    void MapTreeView::Show() {
      ::ShowWindow(this->handle, SW_SHOW);
      ::UpdateWindow(this->handle);
    }

    LRESULT MapTreeView::ProcessWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
      /*switch (msg) {
      case WM_LBUTTONUP:
        {
          MessageBox(this->handle, _T("ボタンがクリックされた"), _T("Shrimp"), MB_ICONINFORMATION);
        }
        break;
        }*/
      //const MapTreeViewWC& mapTreeViewWC = MapTreeViewWC::GetInstance();
      return defaultWndProc(this->handle, msg, wParam, lParam);
    }

  }
}
