#include"textEntity.cpp"

class CircleEntity : public CoordinateBasedEntity {
protected:
  double radius;

public:
  CircleEntity(World2D * world, double r) : CoordinateBasedEntity(world) {
    radius = r;
  }
  CircleEntity(double r, World2D * world) : CoordinateBasedEntity(world) {
    radius = r;
  }
  CircleEntity(World2D * world) : CoordinateBasedEntity(world) {
    radius = 1;
  }

  //getters

  double getRadius() { return radius; }

  //setters

  void setRadius(double r) { radius = r; }

  //virts

  void draw() {
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(pos->getX(), pos->getY());

    world->getViewer()->getWindow()->draw(circle);
  }
};
