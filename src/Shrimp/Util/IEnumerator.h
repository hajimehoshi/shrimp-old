#ifndef SHRIMP_UTIL_IENUMERATOR_H
#define SHRIMP_UTIL_IENUMERATOR_H

namespace Shrimp {
  namespace Util {

    template<class TItem>
      class IEnumerator {
    public:
      virtual ~IEnumerator() { };
      virtual const TItem& GetCurrent() const = 0;
      virtual bool MoveNext() = 0;
    };

  }
}

#endif
