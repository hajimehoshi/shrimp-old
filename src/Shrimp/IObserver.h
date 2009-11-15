#ifndef SHRIMP_IOVSERVER_H
#define SHRIMP_IOVSERVER_H

#include <string>

namespace Shrimp {

  class IObserver {
  public:
    IObserver() { }
    virtual ~IObserver() { };
    virtual void Notify(const std::string& property) = 0;
  };

}

#ifdef __TEST

namespace Shrimp {

  class MockObserver : public IObserver {
  public:
    void Clear() {
      this->LastNotifiedProperty = "";
    }
    const std::string& GetLastNotifiedProperty() {
      return this->LastNotifiedProperty;
    }
    void Notify(const std::string& property) {
      this->LastNotifiedProperty = property;
    }
  private:
    std::string LastNotifiedProperty;
  };

#endif
  
}

#endif
