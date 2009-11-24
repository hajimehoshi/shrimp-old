#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <algorithm>
#include <vector>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class Observers : private Uncopyable {
    public:
      typedef typename std::vector<T>::const_iterator const_iterator;
    public:
      void Add(T observer) {
        this->observers.push_back(observer);
      }
      const_iterator begin() {
        return this->observers.begin();
      }
      const_iterator end() {
        return this->observers.end();
      }
      void Remove(T observer) {
        typename std::vector<T>::reverse_iterator rit =
          std::find(this->observers.rbegin(),
                    this->observers.rend(),
                    observer);
        assert(rit != this->observers.rend());
        this->observers.erase(--rit.base());
      }
    private:
      std::vector<T> observers;
    };

  }
}

#endif
