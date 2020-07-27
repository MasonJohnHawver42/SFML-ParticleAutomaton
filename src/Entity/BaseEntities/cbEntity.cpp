#include"entity2D.cpp"

class CoordinateBasedEntity : public Entity2D {
protected:
  Vector<double> * pos;

public:
  CoordinateBasedEntity(double x, double y, World2D * wrld) : Entity2D(wrld) {
    pos = new Vector<double>(x, y);
  }
  CoordinateBasedEntity(World2D * wrld) : Entity2D(wrld) {
    pos = new Vector<double>(0, 0);
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
