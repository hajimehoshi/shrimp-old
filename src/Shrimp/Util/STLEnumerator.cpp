#include "Shrimp/Util/STLEnumerator.h"

#ifdef __TEST

#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>

namespace Shrimp {
  namespace Util {

    TEST(STLEnumeratorTest, List) {
      std::list<int> l;
      l.push_back(3);
      l.push_back(1);
      l.push_back(4);
      l.push_back(1);
      l.push_back(5);
      std::auto_ptr< IEnumerator<int> > e =
        std::auto_ptr< IEnumerator<int> >(new STLEnumerator< std::list<int> >(l));
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(3, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(1, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(4, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(1, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(5, e->GetCurrent());
      ASSERT_EQ(false, e->MoveNext());
    }

    TEST(STLEnumeratorTest, Set) {
      std::set<int> s;
      s.insert(3);
      s.insert(1);
      s.insert(4);
      s.insert(1);
      s.insert(5);
      std::auto_ptr< IEnumerator<int> > e =
        std::auto_ptr< IEnumerator<int> >(new STLEnumerator< std::set<int> >(s));
      std::set<int> expected;
      ASSERT_EQ(true, e->MoveNext());
      expected.insert(e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      expected.insert(e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      expected.insert(e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      expected.insert(e->GetCurrent());
      ASSERT_TRUE(expected == s);
      ASSERT_EQ(false, e->MoveNext());
    }

    TEST(STLEnumeratorTest, Vector) {
      std::vector<int> v;
      v.push_back(3);
      v.push_back(1);
      v.push_back(4);
      v.push_back(1);
      v.push_back(5);
      std::auto_ptr< IEnumerator<int> > e =
        std::auto_ptr< IEnumerator<int> >(new STLEnumerator< std::vector<int> >(v));
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(3, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(1, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(4, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(1, e->GetCurrent());
      ASSERT_EQ(true, e->MoveNext());
      ASSERT_EQ(5, e->GetCurrent());
      ASSERT_EQ(false, e->MoveNext());
    }

  }
}

#endif
