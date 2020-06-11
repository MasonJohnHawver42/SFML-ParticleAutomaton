#include"../BaseEntities/Particle/baseParticle.cpp"
#include<string>


class Button : public Entity2D {
private:
  RectangleEntity * body;

  bool clicked;

  string name; // todo latter

public:
    Button(RectangleEntity * rect, World2D * wrld) : Entity2D(wrld) {
      body = rect;
      body->setWorld(getWorld());

      clicked = 0;
    }

    Button(World2D * wrld) : Entity2D(wrld) {
      body = new RectangleEntity(.1, .1);
      body->setWorld(getWorld());

      clicked = 0;
      std::cout << clicked << '\n';
    }

    //get

    RectangleEntity * getBody() { return body; }

    bool isClicked() { return clicked; }

    //modd

    void click() {
      clicked = 1 - clicked;
    }

    void reset() {
      clicked = 0;
    }

    //virtual

    virtual void setWorld(World2D * w) {
      Entity2D::setWorld(w);
      body->setWorld(getWorld());
    }

    void drawText() {
      sf::Text text;
      text.setFont(*world->getAssetMng()->getFont(0)); // font is a sf::Font
      text.setString("Reset");
      text.setCharacterSize(120); // in pixels, not points!
      text.setScale(1.0 / 4800, 1.0 / 4800);
      text.setFillColor(sf::Color::Red);
      text.setPosition(.01, .01);
      text.setStyle(sf::Text::Bold);

      Viewer2D * cam = world->getViewer();
      sf::RenderWindow * window = cam->getWindow();

      //std::cout << "here" << '\n';

      window->draw(text);
    }

    virtual void draw() {
      Viewer2D * cam = world->getViewer();
      sf::RenderWindow * window = cam->getWindow();

      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(body->getWidth(), body->getHeight()));
      rectangle.setPosition(body->getPos()->getX(), body->getPos()->getY());
      rectangle.setFillColor(sf::Color(255, 255, 255, 100 + (100 * !clicked)));

      window->draw(rectangle);
      drawText();
    }

};

class ButtonManager {
private:
  vector<Button*> * buttons;
  World2D * world;

  bool leftClickDown = 0; //latter check for this in user with a keyboard class

public:
  ButtonManager(World2D * wrld) {
    buttons = new vector<Button*>();
    world = wrld;
  }

  //getters

  int getButtonAmt() { buttons->size(); }

  vector<Button*> * getButtons() { return buttons; }

  Button * getButton(int index) { return buttons->at(index); }

  //setters

  void setWorld(World2D * wrld) {
    world = wrld;
  }

  //modders

  void addButton(Button * b) { b->setWorld(world); buttons->push_back(b); }
  void addButton() {
    std::cout << "button added" << '\n';
    Button * b = new Button(world);
    buttons->push_back(b);
  }

  //virtuals

  virtual void update() {
    //determine if a button is pressed

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftClickDown) {

      Vector<double> * sp = world->getUser()->getMouseCursor()->getScreenPos();
      sp->div(world->getViewer()->getWindow()->getDefaultView().getSize().x, world->getViewer()->getWindow()->getDefaultView().getSize().y);


      for(int i = 0; i < buttons->size(); i++) {
        if(buttons->at(i)->getBody()->isInside(sp)) {
          buttons->at(i)->click();
        }
      }

      delete sp;

      leftClickDown = 0;
    }
    else if (!leftClickDown && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
      leftClickDown = 1;
    }

  }

  virtual void draw() {
    sf::View view;
    view.reset(sf::FloatRect(0, 0, 1, 1));
    world->getViewer()->getWindow()->setView(view);

    for(int i = 0; i < buttons->size(); i++) {
      buttons->at(i)->draw();
    }

    world->getViewer()->setView();
  }
};
