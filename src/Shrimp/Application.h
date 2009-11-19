#ifndef SHRIMP_APPLICATION_H
#define SHRIMP_APPLICATION_H

#include "Shrimp/Util/Singleton.h"

namespace Shrimp {

  class Application : public Util::Singleton<Application> {
    friend class Util::Singleton<Application>;
  public:
    int Run();
  private:
    Application() { }
  };

}

#endif
