#include"viewer2D.cpp"

class TargetViewer : public Viewer2D {
private:
  Vector<double> * target;

public:
  TargetViewer(Vector<double> * t) : Viewer2D() {
    target = t;

  }
  TargetViewer() : Viewer2D() {
    target = new Vector<double>(0, 0);
  }

  //getters

  Vector<double> * getTarget() { return target; }

  //setters

  void setTarget(Vector<double> * t) { target = t; }

  //other

  virtual void updatePos() {

    pos->setX(target->getX());
    pos->setY(target->getY());

  }

  virtual void update() {
    Viewer2D::update();
    updatePos();
  }
};
