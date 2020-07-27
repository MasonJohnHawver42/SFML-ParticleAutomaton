#include"button.cpp"


class UserInterface {
private:
  World2D * world;

  ButtonManager * buttonMngr;

  SliderManager * sliderMngr;

public:
  UserInterface(World2D * wrld) {
    world = wrld;

    buttonMngr = new ButtonManager(world);
    sliderMngr = new SliderManager(world);
  }

  //getters

  World2D * getWorld() { return world; }

  ButtonManager * getButtonManager() { return buttonMngr; }

  SliderManager * getSliderManager() { return sliderMngr; }

  //virts

  virtual void update() {
    buttonMngr->update();
    sliderMngr->update();
  }

  virtual void draw() {
    buttonMngr->draw();
    sliderMngr->draw();
  }

};
