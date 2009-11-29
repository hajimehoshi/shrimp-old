#include <cassert>
#include <cstdlib>
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    WNDCLASSEX MapTreeView::wndClass;

    WNDPROC MapTreeView::defaultWndProc;

    MapTreeView::MapTreeView(HWND parent)
      : handle(0) {
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
      //const MapTreeViewWC& mapTreeViewWC = MapTreeViewWC::GetInstance();
      return defaultWndProc(this->handle, msg, wParam, lParam);
    }

  }
}
