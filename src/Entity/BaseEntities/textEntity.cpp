#include"rectEntity.cpp"
#include<string>

class TextEntity : public Entity2D {
private:
  RectangleEntity * bounds;

  sf::Text * text;

public:
  TextEntity(RectangleEntity * b, string t, World2D * wrld) : Entity2D(wrld) {
    bounds = b;
    text = new sf::Text();
    text->setString(t);
    text->setFont(*wrld->getAssetMng()->getFont(0));
  }
  TextEntity(RectangleEntity * b, World2D * wrld) : Entity2D(wrld) {
    bounds = b;
    text = new sf::Text();
    text->setString("Defalt text");
    text->setFont(*wrld->getAssetMng()->getFont(0));
  }
  TextEntity(World2D * wrld) : Entity2D(wrld) {
    bounds = new RectangleEntity(100, 100, 100, 0, wrld);
    text = new sf::Text();
    text->setString("Defalt text");
    text->setFont(*wrld->getAssetMng()->getFont(0));
  }

  //getters

  RectangleEntity * getBounds() { return bounds; }

  sf::Text * getText() { return text; }

  //virtuals

  virtual void draw() {
    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    // set the character size
    text->setCharacterSize(cam->getHeight()); // in pixels, not points!

    text->setPosition(bounds->getPos()->getX(), bounds->getPos()->getY());

    text->setScale(bounds->getHeight() / cam->getHeight(), bounds->getHeight() / cam->getHeight() );

    bounds->setWidth(text->getGlobalBounds().width);

    window->draw(*text);
  }

};
