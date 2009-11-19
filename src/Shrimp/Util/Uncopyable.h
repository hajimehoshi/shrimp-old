#ifndef SHRIMP_UTIL_UNCOPYABLE_H
#define SHRIMP_UTIL_UNCOPYABLE_H

namespace Shrimp {
  namespace Util {

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

