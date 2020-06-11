#include"entity2D.cpp"

class CoordinateBasedEntity : public Entity2D {
protected:
  Vector<double> * pos;

public:
  CoordinateBasedEntity(World2D * wrld) : Entity2D(wrld) {
    pos = new Vector<double>(.1, .1);
  }
  CoordinateBasedEntity() : Entity2D() {
    pos = new Vector<double>(.01, .01);
  }

  ~ CoordinateBasedEntity() {
    delete pos;
    //std::cout << "cb" << '\n';
  }

  //getters

  Vector<double> * getPos() { return pos; }

  //setters

  void setPos(Vector<double> * p) { pos = p; }
  void setPos(double x, double y) {
    pos->setX(x);
    pos->setY(y);
  }

};
