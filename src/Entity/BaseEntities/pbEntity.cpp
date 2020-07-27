#include "cbEntity.cpp"

double gFriction = .7;

class PhysicsBasedEntity : public CoordinateBasedEntity {
protected:
  Vector<double> * vel;
  Vector<double> * acc;

  double mass;

  double friction;


public:
  PhysicsBasedEntity(World2D * world) : CoordinateBasedEntity(world) {
    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    mass = 1;
    friction = gFriction;
  }

  ~ PhysicsBasedEntity() {
    delete vel, acc;
    //std::cout << "pb" << '\n';
  }

  //getters

  Vector<double> * getVel() { return vel; }
  Vector<double> * getAcc() { return acc; }

  //setters

  void setVel(Vector<double> v) { vel->setX(v.getX()); vel->setY(v.getY()); }
  void setAcc(Vector<double> a) { acc->setX(a.getX()); acc->setY(a.getY()); }

  //modifyers

  void applyForce(Vector<double> * force) { acc->add(force->getX() / mass, force->getY() / mass); }
  void applyForce(double xf, double yf) { acc->add(xf / mass, yf / mass); }

  void applyFriction() {
    friction = gFriction;
    if(friction >0 && friction <= 1) { vel->mult(pow(1 - friction, world->getUpdateTimeDelta())); }
  }

  void applyVel() {
    //vel->limitMag(maxSpeed);

    double t = world->getUpdateTimeDelta();
    Vector<double> * v = new Vector<double>(t, t);
    v->mult(*vel);
    pos->add(*v);

    delete v;
  }

  void applyAcc() {
    //acc->limitMag(maxAcc);

    double t = world->getUpdateTimeDelta();
    Vector<double> * a = new Vector<double>(t, t);
    a->mult(*acc);

    vel->add(*a);
    acc->mult(0);

    delete a;
  }

  virtual void update() {
    applyAcc();
    applyVel();
    applyFriction();
  }

};
