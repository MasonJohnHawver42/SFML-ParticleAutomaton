#include"../BaseEntities/Particle/baseParticle.cpp"


string stripZeros(string s) {
  for(int i = s.length() - 1; i >= 0; i--) {
     if (s[i] != '0') {
       return s.substr(0, i + 1);
     }

   }
   return s;
}


class Slider : public Entity2D {
private:
  RectangleEntity * body;
  CircleEntity * grabber;

  TextEntity * text;

  string name;

  double val;

  double min_val;
  double max_val;

  double jump;

  bool ocupied;

  void init() {
    min_val = 100;
    max_val = 400;

    val = 0;
    jump = 1;

    ocupied = 0;

    updateGrabber();
    updateText();
  }

public:
  Slider(RectangleEntity * b, string n, double m1, double m2, double j, double v, World2D * wrld) : Entity2D(wrld) {
    body = b;
    body->setWorld(wrld);
    grabber = new CircleEntity(5., getWorld());
    text = new TextEntity(new RectangleEntity(100., 10., 0., 0., getWorld()), getWorld());

    name = n;

    min_val = min(m1, m2);
    max_val = max(m1, m2);
    jump = j;
    val = 0;
    ocupied = 0;

    setVal(v);

    updateGrabber();
    updateText();

  }

  Slider(RectangleEntity * b, string n, World2D * wrld) : Entity2D(wrld) {
    body = b;
    body->setWorld(wrld);
    grabber = new CircleEntity(5., getWorld());
    text = new TextEntity(new RectangleEntity(100., 10., 0., 0., getWorld()), getWorld());

    name = n;

    init();
  }

  Slider(World2D * wrld) : Entity2D(wrld) {
    body = new RectangleEntity(100., 10., 10., 10., getWorld());
    grabber = new CircleEntity(5., getWorld());

    text = new TextEntity(new RectangleEntity(100., 10., 0., 0., getWorld()), getWorld());

    name = "Default";

    init();
  }

  //getters

  RectangleEntity * getBody() { return body; }
  CircleEntity * getGrabber() { return grabber; }

  double getMax() { return max_val; }
  double getMin() { return min_val; }
  double getVal() { return val; }
  double getJump() {return jump; }

  bool isBeingUsed() { return ocupied; }

  //setters

  virtual void setWorld(World2D * wrld) {
    world = wrld;
    body->setWorld(wrld);
    text->setWorld(wrld);
    grabber->setWorld(wrld);
  }

  void setVal(double v) {
    val = max(min(max_val, v), min_val);

    double p = (val - min_val) / (max_val - min_val);
    p *= body->getWidth() - (body->getHeight());
    p += body->getPos()->getX();

    grabber->getPos()->setX(p);
  }

  //modder

  void use() {
    Vector<double> * mp = world->getUser()->getMouseCursor()->getPos();
    grabber->getPos()->setVector(mp->getX() - (body->getHeight() / 2.0), mp->getY());

    updateGrabber();
    updateVal();
    updateText();
    updateMouse();
  }

  void updateText() {
    double x = body->getPos()->getX() + body->getWidth() + (body->getHeight() / 2.0);
    double y = body->getPos()->getY() + (body->getHeight() / 4.0);

    text->getBounds()->getPos()->setVector(x, y);
    text->getBounds()->setHeight(body->getHeight() / 2.0);
    text->getText()->setString(stripZeros(to_string(val)) + " -> " + name);
  }

  void updateGrabber() {

    double x = max(body->getPos()->getX(), grabber->getPos()->getX());
    x = min(x, body->getPos()->getX() + body->getWidth() - body->getHeight());

    double y = 0; //body->getHeight() / 2.0;
    y += body->getPos()->getY();

    grabber->getPos()->setVector(x, y);
    grabber->setRadius(body->getHeight() / 2.0);
  }

  void updateVal() {
    double p = grabber->getPos()->getX() - body->getPos()->getX();
    p /= body->getWidth() - (body->getHeight());

    p  = (p * (max_val - min_val)) + min_val;

    val = jump * ceil(p / jump);
  }

  void updateMouse() {
    MouseCursor * mc = world->getUser()->getMouseCursor();
    Vector<double> * sp = mc->getScreenPos();
    double y = grabber->getPos()->getY() + (body->getHeight() / 2.0);
    y -= world->getViewer()->getPos()->getY();
    y /= world->getViewer()->getHeight();
    y *= world->getViewer()->getWindow()->getDefaultView().getSize().y;
    double max1 = body->getPos()->getX() + body->getWidth() - (body->getHeight()/ 2.0);
    double min1 = body->getPos()->getX() + (body->getHeight()/ 2.0);
    max1 -= world->getViewer()->getPos()->getX(); min1 -= world->getViewer()->getPos()->getX();
    max1 /= world->getViewer()->getWidth(); min1 /= world->getViewer()->getWidth();
    max1 *= world->getViewer()->getWindow()->getDefaultView().getSize().x; min1 *= world->getViewer()->getWindow()->getDefaultView().getSize().x;
    sf::Mouse::setPosition(sf::Vector2i(min(max(sp->getX(), min1), max1), y), *world->getViewer()->getWindow());

    delete sp;
  }

  void isOcupied() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (body->isInside(world->getUser()->getMouseCursor()->getPos())) {
        ocupied = 1;
      }
      else { ocupied = 0; }
    }

    else {
      ocupied = 0;
    }
  }

  void update() {
    isOcupied();
    if(ocupied) {
      use();
    }
  }

  void draw() {
    //body->draw();
    grabber->draw();
    text->draw();

    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(body->getWidth(), body->getHeight() / 8.0));
    rectangle.setPosition(body->getPos()->getX(), body->getPos()->getY() + ((body->getHeight() * (1. - (1. / 8.0))) / 2.0));
    //rectangle.setFillColor(*color);

    window->draw(rectangle);
  }
};

class SliderManager {
private:
  World2D * world;

  vector<Slider*> * sliders;
  bool ocupied = 0;

public:
  SliderManager(World2D * wrld) {
    world = wrld;
    sliders = new vector<Slider*>();
  }

  //getters

  int getSliderAmt() { sliders->size(); }

  World2D * getWorld() { return world; }

  Slider * getSlider(int index) { return sliders->at(index); }

  bool isBeingUsed() { return ocupied; }

  //setters

  void setWorld(World2D * w) {
    world = w;
    for (int i = 0; i < getSliderAmt(); i++) {
      getSlider(i)->setWorld(w);
    }
  }

  //modders



  void addSlider(Slider * s) { s->setWorld(getWorld()); sliders->push_back(s); }

  void update() {
    ocupied = 0;

    for (int i = 0; i < getSliderAmt(); i++) {
      getSlider(i)->update();
      ocupied += getSlider(i)->isBeingUsed();
    }
  }

  void draw() {
    for (int i = 0; i < getSliderAmt(); i++) {
      getSlider(i)->draw();
    }
  }

};
