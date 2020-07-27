#include "../AssetManager/assetManager.cpp"

class MouseCursor {
protected:
  Vector<double> * pos;
  Vector<double> * lastPos;
  double size;

  Viewer2D * viewer;

  bool leftClickDown;
  bool leftClicked;

public:
  MouseCursor(Viewer2D * v) {
    pos = new Vector<double>(0, 0);
    lastPos = new Vector<double>(0, 0);
    size = 2;

    leftClickDown = 0;
    leftClicked = 0;

    viewer = v;
  }

  //getters

  Viewer2D * getViewer() { return viewer; }

  bool isLeftClickDown() { return leftClickDown; }

  Vector<double> * getScreenPos() {
    sf::Vector2i p = sf::Mouse::getPosition(*viewer->getWindow());
    Vector<double> * sp = new Vector<double>(p.x, p.y);

    return sp;
  }

  Vector<double> * getNormalPos() {
    Vector<double> * np = getScreenPos();

    np->toString();

    return np;
  }

  Vector<double> * getDiff() {
    Vector<double> * diff = new Vector<double>(0, 0);
    diff->add(*pos);
    diff->sub(*lastPos);

    return diff;
  }


  Vector<double> * getPos() { return pos; }

  double getSize() { return size; }

  //setters

  void setViewer(Viewer2D * v) { viewer = v; }

  void setPosFromScreenPos(Vector<double> * sp) {

    lastPos->setX(pos->getX());
    lastPos->setY(pos->getY());

    sf::RenderWindow * window = viewer->getWindow();

    Vector<double> * transform = new Vector<double>(window->getSize().x / viewer->getWidth(), window->getSize().y / viewer->getHeight());

    sp->div(*transform);
    sp->add(*viewer->getPos());

    delete transform;

    pos->setX(sp->getX());
    pos->setY(sp->getY());

  }

  //virtuals

  void limitPos() {

    double minX = viewer->getPos()->getX();
    double minY = viewer->getPos()->getY();

    double maxX = minX + viewer->getWidth();
    double maxY = minY + viewer->getHeight();

    pos->setX(min(maxX, max(minX, pos->getX())));
    pos->setY(min(maxY, max(minY, pos->getY())));

  }

  void updatePos() {
    Vector<double> * sp = getScreenPos();

    setPosFromScreenPos(sp);
    delete sp;

  }

  void updateInput() {
    leftClickDown = sf::Mouse::isButtonPressed(sf::Mouse::Left) * (1 - leftClicked);
    leftClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
  }

  virtual void update() {
    updateInput();
    updatePos();
    limitPos();
  }

  virtual void draw() {

    sf::RenderWindow * window = viewer->getWindow();
    window->setMouseCursorVisible(0);

    sf::CircleShape shape(size);
    shape.setPosition(pos->getX() - size, pos->getY() - size);
    shape.setFillColor(sf::Color(255, 255, 255, 100));

    shape.setOutlineThickness(size * .4);
    shape.setOutlineColor(sf::Color(0, 0, 0, 255));

    window->draw(shape);
  }
};
