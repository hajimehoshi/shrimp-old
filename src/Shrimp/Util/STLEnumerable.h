#ifndef SHRIMP_UTIL_ENUMERABLE_H
#define SHRIMP_UTIL_ENUMERABLE_H

#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class STLEnumerable : private Uncopyable {
    public:
      typedef typename T::const_iterator Iterator;
      STLEnumerable(T& innerContainer)
        : innerContainer(innerContainer) {
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
