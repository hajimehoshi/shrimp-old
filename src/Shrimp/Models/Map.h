#ifndef SHRIMP_MODELS_MAP_H
#define SHRIMP_MODELS_MAP_H

#include <string>

namespace Shrimp {
  namespace Models {

    class Map {
    public:
      Map(std::string name, int width, int height);
      inline int GetHeight() const {
        return this->Height;
      }
      inline const std::string& GetName() const {
        return this->Name;
      }
      inline int GetWidth() const {
        return this->Width;
      }
      void SetHeight(int height);
      void SetName(std::string name);
      void SetWidth(int width);
    private:
      Map(const Map& map);
      Map& operator=(const Map& rhs);
      std::string Name;
      int Width;
      int Height;
    };


  }
}

#endif
