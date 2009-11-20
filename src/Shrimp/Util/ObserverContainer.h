#ifndef SHRIMP_UTIL_OBSERVERCONTAINER_H
#define SHRIMP_UTIL_OBSERVERCONTAINER_H

#include <algorithm>
#include <vector>
#include "Shrimp/Util/STLEnumerator.h"
#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class ObserverContainer : private Uncopyable {
    private:
      typedef std::vector<T> InnerContainerType;
    public:
      typedef typename Util::STLEnumerator<InnerContainerType> Enumerator;
    public:
      void Add(T observer) {
        this->observers.push_back(observer);
      }
      std::auto_ptr< Util::IEnumerator<T> > GetEnumerator() const {
        Enumerator* e = new Enumerator(this->observers);
        return std::auto_ptr< Util::IEnumerator<T> >(e);
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
    };

  }
}

#endif
