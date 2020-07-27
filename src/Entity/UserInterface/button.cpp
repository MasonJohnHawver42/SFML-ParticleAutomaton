#include"slider.cpp"


class Button : public Entity2D {
private:
  RectangleEntity * body;
  TextEntity * text;

  bool clicked;

public:
  Button(RectangleEntity * rect, string t, World2D * wrld) : Entity2D(wrld) {
    body = rect;
    body->setWorld(wrld);
    text = new TextEntity(body, t, wrld);
    clicked = 0;
  }
    Button(RectangleEntity * rect, World2D * wrld) : Entity2D(wrld) {
      body = rect;
      body->setWorld(wrld);
      text = new TextEntity(body, wrld);
      clicked = 0;
    }

    Button(string t, World2D * wrld) : Entity2D(wrld) {
      body = new RectangleEntity(32, 8, 0, 0, wrld);
      text = new TextEntity(body, t, wrld);
      clicked = 0;
    }

    Button(World2D * wrld) : Entity2D(wrld) {
      body = new RectangleEntity(32, 8, 0, 0, wrld);
      text = new TextEntity(body, wrld);
      clicked = 0;
    }

    //get

    RectangleEntity * getBody() { return body; }

    TextEntity * getText() { return text; }

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
      text->setWorld(getWorld());
    }

    virtual void draw() {
      Viewer2D * cam = world->getViewer();
      sf::RenderWindow * window = cam->getWindow();

      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(body->getWidth(), body->getHeight()));
      rectangle.setPosition(body->getPos()->getX(), body->getPos()->getY());
      rectangle.setFillColor(sf::Color(25, 255, 20, 255 + (0 * !clicked)));

      //window->draw(rectangle);
      text->draw();
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

      Vector<double> * sp = world->getUser()->getMouseCursor()->getPos();
      //sp->div(world->getViewer()->getWindow()->getDefaultView().getSize().x, world->getViewer()->getWindow()->getDefaultView().getSize().y);
      for(int i = 0; i < buttons->size(); i++) {
    //    std::cout << "here" << '\n';
        if(buttons->at(i)->getBody()->isInside(sp)) {
      //    std::cout << "hereafter" << '\n';
          buttons->at(i)->click();
        }
    }

      leftClickDown = 0;
    }
    else if (!leftClickDown && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
      leftClickDown = 1;
    }

  }

  virtual void draw() {
    sf::View view;
    //std::cout << world->getViewer()->getPos()->getX() << "  " << world->getViewer()->getPos()->getY() << '\n';
    //view.reset(sf::FloatRect(world->getViewer()->getPos()->getX(), world->getViewer()->getPos()->getY(), 100, 100));
    //world->getViewer()->getWindow()->setView(view);

    for(int i = 0; i < buttons->size(); i++) {
      buttons->at(i)->draw();
    }

    //world->getViewer()->setView();
  }
};
