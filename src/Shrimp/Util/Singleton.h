#ifndef SHRIMP_UTIL_SINGLETON_H
#define SHRIMP_UTIL_SINGLETON_H

#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    template<class T>
      class Singleton : private Uncopyable {
    protected:
      Singleton() { }
      ~Singleton() { }
    public:
      inline static T& GetInstance() {
        static T instance;
        return instance;
      }
    };

  }
}

#endif
