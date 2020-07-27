#include"../Entity/UserInterface/userInterface.cpp"

class Settings : public World2D {
private:
  UserInterface * ui;

  void loadAssets() {
    assetManager->loadFile("assests/Fonts/BarcadeBrawl.ttf");
  }

public:
  Settings(sf::RenderWindow * win, AssetManager * am) : World2D() {

    //setViewer(new Viewer2D(win));

    delete getViewer()->getWindow();

    getViewer()->setWindow(win);

    getViewer()->getPos()->sub(10, 10);

    assetManager = am;

    ui = new UserInterface(this);
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 8, 0, 0, this), "Settings", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 141, this), "Back", this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 11, this), "Atraction Mean", -20, 20, .1, atractionMean, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 21, this), "Atraction STD", 0, 20, .1, atractionSTD, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 31, this), "Repultion Mean", -20, 20, .1, repultionMean, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 41, this), "Repultion STD", 0, 20, .1, repultionSTD, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 51, this), "Min Reach Lower", 0, 20, 1, minReachLower, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 61, this), "Min Reach Upper", 0, 40, 1, minReachUpper, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 71, this), "Max Reach Lower", 0, 150, 1, maxReachLower, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 81, this), "Max Reach Upper", 0, 200, 1, maxReachUpper, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 91, this), "Friction Coef", 0, 1, .1, gFriction, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 101, this), "Particle Amt", 0, 400, 1, particleNum, this));
    ui->getSliderManager()->addSlider(new Slider(new RectangleEntity(100, 6, 0, 111, this), "Particle Amt", 1, 40, 1, particleTypeAmt, this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 127, this), "Warped Bounds", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 133, this), "Circle Bounds", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 121, this), "Rectangle Bounds", this));

    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 260, this), "Produced By: Mason Hawver \n\nCode @ github.com/MasonJohnHawver42/ParticleAutomaton \n\nInspired By: Code Parade and Clusters by Jeffery Ventrella", this));
  }

  void uiReaction() {
    Button * backButton = ui->getButtonManager()->getButton(1);

    if(backButton->isClicked()) {
      cont = 0;
      backButton->reset();
    }

    atractionMean = ui->getSliderManager()->getSlider(0)->getVal();
    atractionSTD = ui->getSliderManager()->getSlider(1)->getVal();

    repultionMean = ui->getSliderManager()->getSlider(2)->getVal();
    repultionSTD = ui->getSliderManager()->getSlider(3)->getVal();

    minReachLower = ui->getSliderManager()->getSlider(4)->getVal();
    minReachUpper = ui->getSliderManager()->getSlider(5)->getVal();

    maxReachLower = ui->getSliderManager()->getSlider(6)->getVal();
    maxReachUpper = ui->getSliderManager()->getSlider(7)->getVal();

    if (ui->getButtonManager()->getButton(2)->isClicked()) {
      warpedBounds = 1;
      circleBounds = 0;
      ui->getButtonManager()->getButton(2)->reset();
    }

    if (ui->getButtonManager()->getButton(3)->isClicked()) {
      warpedBounds = 0;
      circleBounds = 1;
      ui->getButtonManager()->getButton(3)->reset();
    }

    if (ui->getButtonManager()->getButton(4)->isClicked()) {
      warpedBounds = 0;
      circleBounds = 0;
      ui->getButtonManager()->getButton(4)->reset();
    }

    if(warpedBounds) {
      ui->getButtonManager()->getButton(2)->getText()->getText()->setString("Warped Bounds -> On");
      ui->getButtonManager()->getButton(3)->getText()->getText()->setString("Circle Bounds -> Off");
      ui->getButtonManager()->getButton(4)->getText()->getText()->setString("Rectangle Bounds -> Off");
    }
    else if(circleBounds) {
      ui->getButtonManager()->getButton(2)->getText()->getText()->setString("Warped Bounds -> Off");
      ui->getButtonManager()->getButton(3)->getText()->getText()->setString("Circle Bounds -> On");
      ui->getButtonManager()->getButton(4)->getText()->getText()->setString("Rectangle Bounds -> Off");
    }
    else {
      ui->getButtonManager()->getButton(2)->getText()->getText()->setString("Warped Bounds -> Off");
      ui->getButtonManager()->getButton(3)->getText()->getText()->setString("Circle Bounds -> Off");
      ui->getButtonManager()->getButton(4)->getText()->getText()->setString("Rectangle Bounds -> On");
    }

    gFriction = ui->getSliderManager()->getSlider(8)->getVal();
    particleNum = ui->getSliderManager()->getSlider(9)->getVal();
    particleTypeAmt = ui->getSliderManager()->getSlider(10)->getVal();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) & !ui->getSliderManager()->isBeingUsed())  {
      getViewer()->getPos()->sub(*user->getMouseCursor()->getDiff());
      user->getMouseCursor()->getPos()->sub(*user->getMouseCursor()->getDiff());
    }
  }

  virtual void start() {
    cont = 1;
  }

  virtual void update() {
    World::update();
        user->update();
    ui->update();
    uiReaction();
  }


  virtual void updateFrame() {
    sf::RenderWindow * window = getViewer()->getWindow();

    window->clear(sf::Color(25, 0, 20));

    getViewer()->update();

    ui->draw();

    user->getMouseCursor()->draw();

    window->display();
  }

  void open() {
    double fps = 60.0;

    sf::Clock * clock = new sf::Clock();

    start();

    while (continueGame()){

      if(clock->getElapsedTime().asSeconds() > 1. / fps) {
        updateFrame();
        clock->restart();
      }

      update();

    }

  }
};
