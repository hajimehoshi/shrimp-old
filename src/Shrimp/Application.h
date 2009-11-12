#ifndef SHRIMP_APPLICAION_H
#define SHRIMP_APPLICAION_H

namespace Shrimp {
  class Application {
  public:
    int Run();
  private:
    Application() { }
    Application(const Application& rhs);
    Application& operator=(const Application& rhs);
  public:
    static Application& GetInstance() {
      static Application instance;
      return instance;
    }
  };
}

#endif
