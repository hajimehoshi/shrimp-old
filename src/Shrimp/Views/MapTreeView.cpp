#include <cassert>
#include <cstdlib>
#include <vector>
#include "Shrimp/Views/MapTreeView.h"

namespace Shrimp {
  namespace Views {

    std::wstring UTF8ToUTF16LE(const std::string& str) {
      int wTextLength = ::MultiByteToWideChar(CP_UTF8,
                                              MB_ERR_INVALID_CHARS,
                                              str.c_str(),
                                              str.length(),
                                              0,
                                              0);
      if (0 < wTextLength) {
        std::vector<wchar_t> buffer(wTextLength + 1);
        ::MultiByteToWideChar(CP_UTF8,
                              MB_ERR_INVALID_CHARS,
                              str.c_str(),
                              str.length(),
                              &buffer[0],
                              wTextLength);
        return std::wstring(&buffer[0]);
      } else {
        return std::wstring(0);
      }
    }

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
                       WS_CHILD | WS_VISIBLE,
                       200, 200, 100, 100,
                       parent,
                       0,
                       GetModuleHandle(0),
                       this);
      // this->handle is set on processing WM_NCCREATE in WndProc
      assert(this->handle);
      this->AddItem(0, 0, "ほげ");
      this->AddItem(1, 0, "ふが");
      this->AddItem(2, 0, "ぴよ");
      this->RemoveItem(1);
    }

    MapTreeView::~MapTreeView() {
      ::DestroyWindow(this->handle);
    }

    void MapTreeView::AddItem(int id, int, std::string text) {
      TV_INSERTSTRUCT tvInsertStruct;
      ::ZeroMemory(&tvInsertStruct, sizeof(tvInsertStruct));
      tvInsertStruct.hInsertAfter = TVI_LAST;
      tvInsertStruct.hParent = TVI_ROOT;
      tvInsertStruct.item.mask = TVIF_TEXT;
      std::wstring wText = UTF8ToUTF16LE(text);
      WCHAR* wText2 = new WCHAR[wText.length() + 1];
      ::CopyMemory(wText2, wText.c_str(), (wText.length() + 1) * sizeof(wText2[0]));
      tvInsertStruct.item.pszText = wText2;
      HTREEITEM treeItem = TreeView_InsertItem(this->handle, &tvInsertStruct);
      delete[] wText2;
      assert(this->treeItems.find(id) == this->treeItems.end());
      this->treeItems.insert(TreeItems::value_type(id, treeItem));
    }

    void MapTreeView::RemoveItem(int id) {
      TreeItems::iterator it = this->treeItems.find(id);
      assert(it != this->treeItems.end());
      TreeView_DeleteItem(this->handle, it->second);
      this->treeItems.erase(it);
    }

    void MapTreeView::Show() {
      assert(this->handle); // TODO: remove it
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

#ifdef __TEST

#include <gtest/gtest.h>

namespace Shrimp {
  namespace Views {

    TEST(UTF8ToUTF16LE, UTF8ToUTF16LE) {
      ASSERT_EQ(3u, UTF8ToUTF16LE("foo").length());
      ASSERT_EQ(L"foo", UTF8ToUTF16LE("foo"));
      ASSERT_EQ(3u, UTF8ToUTF16LE("日本語").length());
      ASSERT_EQ(L"日本語", UTF8ToUTF16LE("日本語"));
    }

  }
}

#endif
