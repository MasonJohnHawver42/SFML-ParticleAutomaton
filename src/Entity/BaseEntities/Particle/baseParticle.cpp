#include"particleType.cpp"

double mod(double v, double n) {
  return ((v < 0 ? 1: 0) * n) + fmod(v, n);
}

bool warpedBounds = 0;
bool circleBounds = 0;

class BaseParticle : public PhysicsBasedEntity  {
protected:
  ParticleType * type;
  CircleEntity * body;

  int id;
  static int lid;

  void initID() {
    id = lid;
    lid++;
  }

public:
  BaseParticle(World2D * wrld, ParticleType * t) : PhysicsBasedEntity(wrld) {
    type = t;

    body = new CircleEntity(wrld, 1);
    body->setPos(getPos());
    initID();
  }
  BaseParticle(World2D * wrld) : PhysicsBasedEntity(wrld) {
    type = nullptr;

    body = new CircleEntity(wrld, 1);
    body->setPos(getPos());
    initID();
  }

  virtual ~ BaseParticle() {
     delete type;
     delete body;
  }

  //getters

  ParticleType * getType() { return type; }

  CircleEntity * getBody() { return body; }

  int getID() { return id; }

  //setters

  void setType(ParticleType * t) { type = t; }

  void setBody(CircleEntity * b) { body = b; body->setWorld(getWorld()); body->setPos(getPos());}

  //modders

  void applyBounds(RectangleEntity * bounds) {
    pos->sub(*bounds->getPos());
    //pos->add(body->getRadius() * 2);
    pos->setX(max((body->getRadius() * 2), min(pos->getX(), bounds->getWidth() - (body->getRadius() * 2))));
    pos->setY(max((body->getRadius() * 2), min(pos->getY(), bounds->getHeight() - (body->getRadius() * 2))));
    pos->add(*bounds->getPos());
    //pos->sub(body->getRadius() * 2);
  }

  void applyCircleBounds(RectangleEntity * bounds) {
    Vector<double> * c = new Vector<double>(0, 0);
    c->add(bounds->getWidth(), bounds->getHeight());
    c->div(2.0);
    c->add(*bounds->getPos());

    double d = c->getDis(*pos);
    double rs = (min(bounds->getWidth(), bounds->getHeight()) / 2.0) * .8 ;
    double rb = (min(bounds->getWidth(), bounds->getHeight()) / 2.0) * 1 ;

    if( d > rs ) {
      double m = min(1.0, (d - rs) / (rb - rs));

      Vector<double> * p = new Vector<double>(0, 0);
      p->add(*pos);
      p->sub(*c);
      p->div(d);

      double v = p->Dot(*vel);

      Vector<double> * f = new Vector<double>(1, 1);
      f->mult(abs(v));
      f->mult(*p);

      acc->mult(0);

      //vel->mult(pow(0, world->getUpdateTimeDelta()));

      p->mult(-100 * m);

      applyForce(p);

      delete p, f;
    }

    rb = sqrt(pow(bounds->getWidth() + body->getRadius(), 2.0) + pow(bounds->getHeight() + body->getRadius(), 2.0)) / 2.0;

    if( d > rb ) {
      getPos()->setY((normalRand(0, .3) * bounds->getHeight() / 2.0) + c->getY());
      getPos()->setX((normalRand(0, .3) * bounds->getWidth() / 2.0) + c->getX());
    }

    delete c;
  }

  void applyWarpedBounds(RectangleEntity * bounds) {
    pos->sub(*bounds->getPos());
    pos->add(body->getRadius() * 2);
    pos->setX(mod(pos->getX(), bounds->getWidth() + (body->getRadius() * 4)));
    pos->setY(mod(pos->getY(), bounds->getHeight() + (body->getRadius() * 4)));
    pos->add(*bounds->getPos());
    pos->sub(body->getRadius() * 2);
  }

  void applyAtraction(BaseParticle * part, RectangleEntity * bounds) {
    if(part && part->getType() && type) {

      Vector<double> * p = new Vector<double>(0, 0);
      p->add(*part->getPos());
      p->sub(*pos);

      int index = type->getIndex(part->getType());

      double d = p->getMag();
      double a = type->getAtraction(index);
      double r = type->getRepultion(index);

      double minR = ((2 * body->getRadius()) + type->getMinReach(index));
      double maxR = type->getMaxReach(index);
      double range = maxR - minR;

      //std::cout << d << '\n';

      double f = a * (-abs((2*(d - minR) / range) - 1) + 1) * (d < maxR ? 1: 0) * (d < minR ? (a < 0 ? -1 : 1) : 1);
      p->setMag(f);

      if(d < minR) {
        //std::cout << rand() << '\n';
        //double f = -1 * abs(a) * ((1.0 / d) - (1.0 / minR));
        //f = (d / minR) - abs(a); // a(-abs((2*(d - minR) / range) - 1) + 1) * (d < maxR ? 1: 0)
        applyForce(p);
      }
      else if(minR < d && d < maxR) {
        //double f = (((-2 * a) / range) * abs(d - (range / 2) - minR)) + a;
        //p->setMag(f);
        part->applyForce(p);
      }
      delete p;

      //std::cout << "here" << '\n';
    //  delete p, a;
    }
  }

  //virts

  virtual void setWorld(World2D * w) { world = w; body->setWorld(world); }

  virtual void draw() {
    sf::CircleShape circle;
    circle.setRadius(body->getRadius());
    circle.setPosition(pos->getX(), pos->getY());
    circle.setFillColor(*type->getColor());

    world->getViewer()->getWindow()->draw(circle);
  }

  virtual bool equal(BaseParticle * part) {
    return (id == part->getID());
  }

};
int BaseParticle::lid = 0;
