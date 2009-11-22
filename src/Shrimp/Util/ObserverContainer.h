#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <algorithm>
#include <vector>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class ObserverContainer : private Uncopyable {
    public:
      typedef std::vector<T> Observers;
    public:
      void Add(T observer) {
        this->observers.push_back(observer);
      }
      const Observers& GetObservers() const {
        return this->observers;
      }
      void Remove(T observer) {
        typename Observers::reverse_iterator rit =
          std::find(this->observers.rbegin(),
                    this->observers.rend(),
                    observer);
        assert(rit != this->observers.rend());
        this->observers.erase(--rit.base());
      }
    private:
      Observers observers;
    };

  }
}

#endif
