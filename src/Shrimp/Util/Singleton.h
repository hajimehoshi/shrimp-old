#ifndef SHRIMP_UTIL_SINGLETON_H
#define SHRIMP_UTIL_SINGLETON_H

#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {
  namespace Util {

    /*
     * This class is NOT for polymorphism.
     * Don't call delete operator for a pointer of this class!
     */
    template<class T>
      class Singleton : private Uncopyable {
    protected:
      Singleton() { }
      ~Singleton() throw() { }
    public:
      inline static T& GetInstance() {
        static T instance;
        return instance;
      }
    };

  }
}

#endif
