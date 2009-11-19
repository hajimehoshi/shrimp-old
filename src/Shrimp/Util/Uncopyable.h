#ifndef SHRIMP_UTIL_UNCOPYABLE_H
#define SHRIMP_UTIL_UNCOPYABLE_H

namespace Shrimp {
  namespace Util {

    /*
     * This class is NOT for polymorphism.
     * Don't call delete operator for a pointer of this class!
     */
    class Uncopyable {
    protected:
      Uncopyable() { }
      ~Uncopyable() { }
    private:
      Uncopyable(const Uncopyable&);
      Uncopyable& operator=(const Uncopyable&);
    };

  }
}

#endif

