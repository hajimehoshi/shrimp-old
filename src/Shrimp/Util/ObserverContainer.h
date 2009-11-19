#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <algorithm>
#include <vector>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class ObserverContainer : private Uncopyable {
    private:
      typedef std::vector<T> InnerContainerType;
    public:
      typedef typename InnerContainerType::const_iterator CIterator;
      void Add(T observer) {
        this->Observers.push_back(observer);  
      }
      inline CIterator Begin() const {
        return this->Observers.begin();
      }
      inline CIterator End() const {
        return this->Observers.end();
      }
      void Remove(T observer) {
        typename InnerContainerType::reverse_iterator rit =
          std::find(this->Observers.rbegin(),
                    this->Observers.rend(),
                    observer);
        assert(rit != this->Observers.rend());
        this->Observers.erase(--rit.base());
      }
    private:
      InnerContainerType Observers;
    };

  }
}

#endif
