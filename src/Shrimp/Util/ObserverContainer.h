#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <set>
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class ObserverContainer : private Uncopyable {
    public:
      typedef std::set<T*> ContainerInnerType;
      typedef typename ContainerInnerType::const_iterator Iterator;
      inline void Add(T& observer) {
        this->Observers.insert(&observer);  
      }
      inline Iterator Begin() const {
        return this->Observers.begin();
      }
      inline Iterator End() const {
        return this->Observers.end();
      }
      inline void Remove(T& observer) {
        Iterator it = this->Observers.find(&observer);
        assert(it != this->Observers.end());
        this->Observers.erase(it);
      }
    private:
      ContainerInnerType Observers;
    };

  }
}

#endif
