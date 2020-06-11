#include"button.cpp"


class UserInterface {
private:
  World2D * world;

  ButtonManager * buttonMngr;

public:
  UserInterface(World2D * wrld) {
    world = wrld;

    buttonMngr = new ButtonManager(world);
  }

  //getters

  World2D * getWorld() { return world; }

  ButtonManager * getButtonManager() { return buttonMngr; }

  //virts

  virtual void update() {
    buttonMngr->update();
  }

  virtual void draw() {
    buttonMngr->draw();
  }

};
