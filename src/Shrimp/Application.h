#ifndef SHRIMP_APPLICAION_H
#define SHRIMP_APPLICAION_H

#include "Shrimp/Util/Uncopyable.h"

namespace Shrimp {

  class Application : private Util::Uncopyable {
  public:
    int Run();
  private:
    Application() { }
  public:
    static Application& GetInstance() {
      static Application instance;
      return instance;
    }
  };

}

#endif
