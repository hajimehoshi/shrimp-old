#ifndef SHRIMP_UTIL_ENUMERATOR_H
#define SHRIMP_UTIL_ENUMERATOR_H

#include <cassert>
#include "Shrimp/Util/IEnumerator.h"

namespace Shrimp {
  namespace Util {

    template<class TContainer>
      class STLEnumerator : public IEnumerator<typename TContainer::value_type> {
    public:
      STLEnumerator(const TContainer& innerContainer_)
        : innerContainer(innerContainer_),
        it(this->innerContainer.begin()), isInit(true) {
      }
      virtual const typename TContainer::value_type& GetCurrent() const {
        assert(!this->isInit);
        return *this->it;
      }
      virtual bool MoveNext() {
        if (this->isInit) {
          this->isInit = false;
          return true;
        } else if (this->it != this->innerContainer.end()) {
          ++this->it;
          if (this->it != this->innerContainer.end()) {
            return true;
          } else {
            return false;
          }
        } else {
          return false;
        }
      }
    private:
      const TContainer& innerContainer;
      typename TContainer::const_iterator it;
      bool isInit;
    };

  }
}

#endif
