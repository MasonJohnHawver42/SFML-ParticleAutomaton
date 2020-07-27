#include "entity.cpp"

class Entity2D : Entity {
protected:
  World2D * world;

public:
  Entity2D() : Entity() {
    world = nullptr;
    std::cout << "World NOT Defined! why?" << '\n';
  }

  Entity2D(World2D * wrld) : Entity() {
    world = wrld;
  }

  // getters

  World2D * getWorld() { return world; }

  //setters

  virtual void setWorld(World2D * w) { world = w; }
};
