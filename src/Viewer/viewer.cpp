#include <SFML/Graphics.hpp>
#include "../CustomDataStructures/vector.cpp"

class Viewer {
protected:
  sf::RenderWindow * window;

public:
  Viewer(sf::RenderWindow * w) {
    window = w;
  }

  Viewer() {
    window = new sf::RenderWindow(sf::VideoMode(1200, 1200), "Demo Game 66");
  }

  //getters

  sf::RenderWindow * getWindow() { return window; }

  //setters

  void setWindow(sf::RenderWindow * w) { window = w; }

  //other

  virtual void updateWindow() {}

};
