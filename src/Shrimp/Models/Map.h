#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <list>
#include <string>
#include "Shrimp/IObserver.h"

namespace Shrimp {
  namespace Models {

    class Map {
    public:
      Map(std::string name, int width, int height);
      inline void AddObserver(IObserver& observer) {
        this->Observers.push_back(&observer);
      }
      inline int GetHeight() const {
        return this->Height;
      }
      inline const std::string& GetName() const {
        return this->Name;
      }
      inline int GetWidth() const {
        return this->Width;
      }
      inline void RemoveObserver(IObserver& observer) {
        this->Observers.remove(&observer);
      }
      void SetHeight(int height);
      void SetName(const std::string& name);
      void SetWidth(int width);
    private:
      Map(const Map& map);
      Map& operator=(const Map& rhs);
      void NotifyObservers(const std::string& name);
      std::string Name;
      int Width;
      int Height;
      std::list<IObserver*> Observers;
    };

  }
}

#endif
