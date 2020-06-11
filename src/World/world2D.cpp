#include "world.cpp"

class World2D : public World {
protected:
  User * user;

public:

  World2D() : World() {
    user = new User();
  }

  //getters

  Viewer2D * getViewer() { return user->getViewer(); }

  User * getUser() { return user; }

  //setters

  void setViewer(Viewer2D * v) { user->setViewer(v); }

};
