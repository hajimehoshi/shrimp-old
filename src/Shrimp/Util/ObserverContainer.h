#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <algorithm>
#include <vector>
#include "Shrimp/Util/STLEnumerable.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class ObserverContainer : private Uncopyable {
    private:
      typedef std::vector<T> InnerContainerType;
    public:
      typedef typename Util::STLEnumerable<InnerContainerType> STLEnumerable;
    public:
      ObserverContainer()
        : observers(), enumerable(this->observers) {
      }
      void Add(T observer) {
        this->observers.push_back(observer);
      }
      const STLEnumerable& GetEnumerable() const {
        return this->enumerable;
      }
      void Remove(T observer) {
        typename InnerContainerType::reverse_iterator rit =
          std::find(this->observers.rbegin(),
                    this->observers.rend(),
                    observer);
        assert(rit != this->observers.rend());
        this->observers.erase(--rit.base());
      }
    private:
      InnerContainerType observers;
      STLEnumerable enumerable;
    };

  }
}

#endif
