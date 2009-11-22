#include "Shrimp/Util/STLEnumerable.h"

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
      STLEnumerable< std::list<int> >e(l);
      ASSERT_TRUE(l.begin() == e.Begin());
      ASSERT_TRUE(l.end() == e.End());
    }
 
    TEST(STLEnumeratorTest, Set) {
      std::set<int> s;
      s.insert(3);
      s.insert(1);
      s.insert(4);
      s.insert(1);
      s.insert(5);
      STLEnumerable< std::set<int> >e(s);
      ASSERT_TRUE(s.begin() == e.Begin());
      ASSERT_TRUE(s.end() == e.End());
    }
 
    TEST(STLEnumeratorTest, Vector) {
      std::vector<int> v;
      v.push_back(3);
      v.push_back(1);
      v.push_back(4);
      v.push_back(1);
      v.push_back(5);
      STLEnumerable< std::vector<int> >e(v);
      ASSERT_TRUE(v.begin() == e.Begin());
      ASSERT_TRUE(v.end() == e.End());
    }

  }
}

#endif
