#ifndef SHRIMP_UTIL_ENUMERABLE_H
#define SHRIMP_UTIL_ENUMERABLE_H

#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class Enumerable : private Uncopyable {
    public:
      typedef typename T::const_iterator Iterator;
      Enumerable(T& innerContainer_)
        : innerContainer(innerContainer_) {
      }
      inline Iterator Begin() const {
        return this->innerContainer.begin();
      }
      inline Iterator End() const {
        return this->innerContainer.end();
      }
    private:
      T& innerContainer;
    };

  }
}

#endif
