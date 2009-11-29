#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    MapTreeView::MapTreeView(HWND parent)
      : handle(0) {
      const MapTreeViewWC& mapTreeViewWC = MapTreeViewWC::GetInstance();
      const WNDCLASSEX& wc = mapTreeViewWC.GetWndClass();
      ::CreateWindowEx(WS_EX_CLIENTEDGE,
                       wc.lpszClassName,
                       0,
                       WS_CHILD | WS_VISIBLE,
                       200, 200, 100, 100,
                       parent,
                       0,
                       GetModuleHandle(0),
                       this);
      // this->handle is set on processing WM_NCCREATE in WndProc
      assert(this->handle);
    }

    MapTreeView::~MapTreeView() {
      ::DestroyWindow(this->handle);
    }

    void MapTreeView::Show() {
      assert(this->handle);
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
      const MapTreeViewWC& mapTreeViewWC = MapTreeViewWC::GetInstance();
      return mapTreeViewWC.GetDefaultWndProc()(this->handle, msg, wParam, lParam);
    }

    MapTreeViewWC::MapTreeViewWC()
      : defaultWndProc(0) {
      WNDCLASSEX& wc = this->wndClass;
      ::ZeroMemory(&wc, sizeof(wc));
      wc.cbSize = sizeof(wc);
      ::GetClassInfoEx(0, WC_TREEVIEW, &wc);
      this->defaultWndProc = wc.lpfnWndProc;
      wc.lpfnWndProc = &WndProc<MapTreeView>;
      wc.lpszClassName = _T("ShrimpMapTreeView");
      if (!::RegisterClassEx(&wc)) {
        std::abort();
      }
    }

  }
}
