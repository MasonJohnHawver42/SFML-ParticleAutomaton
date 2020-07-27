#include"settings.cpp"

class ParticleWorld : public World2D {
private:
  UserInterface * ui;

  vector<BaseParticle*> * particles;
  vector<ParticleType*> * types;

  RectangleEntity * bounds;

  int target = -1;

  Settings * menu;

  void loadAssets() {
    assetManager->loadFile("assests/Fonts/BarcadeBrawl.ttf");
  }

  void initBounds() {
    bounds = new RectangleEntity(100, 100, this);
    updateBounds();
    bounds->setWidth(getViewer()->getWidth());
    bounds->setHeight(getViewer()->getHeight());
  }

public:
  ParticleWorld() : World2D() {
    particles = new vector<BaseParticle*>();
    types = new vector<ParticleType*>();

    initBounds();

    //setViewer(new Viewer2D());

    initWorld();

    loadAssets();

    ui = new UserInterface(this);
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 16, this), "Reset", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 11, this), "Settings", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 8, 0, 0, this), "Emergant Particle Life", this));
    ui->getButtonManager()->addButton(new Button(new RectangleEntity(32, 4, 0, 21, this), "Quit", this));

    menu = new Settings(getViewer()->getWindow(), assetManager);

    getViewer()->getPos()->sub(10, 10);
  }

  //getters

  int getParticleAmt() { return particles->size(); }
  int getTypeAmt() { return types->size(); }

  BaseParticle * getParticle(int index) { return particles->at(index); }
  ParticleType * getType(int index) { return types->at(index); }

  RectangleEntity * getBounds() { return bounds; }

  //setters

  void setTarget(int index) {
    target =  index;
  }

  void updateTarget() {
    if(target >= 0 && target < particles->size()) {
      Vector<double> * tar = dynamic_cast<TargetViewer*>(getViewer())->getTarget();
      Vector<double> * partPos = getParticle(target)->getPos();

      tar->setX(partPos->getX() - (getViewer()->getWidth() / 2.0));
      tar->setY(partPos->getY() - (getViewer()->getHeight() / 2.0));
    }
  }

  //modders

  void initWorld() {
    createRandomTypes(particleTypeAmt);
    createRandomParts(particleNum);
  }

  void addParticle(BaseParticle * part) {
    if(part->getType()) {
      for(int i = 0; i < types->size(); i++) {
        if(types->at(i)->equal(part->getType())) {
          particles->push_back(part);
          part->setWorld(this);
          return;
        }
      }

      addType(part->getType());
      particles->push_back(part);
      part->setWorld(this);
    }
  }

  void addRandomParticle(BaseParticle * part) {
    //random type, pos

    int typeIndex = rand() % getTypeAmt();
    part->setType(getType(typeIndex));

    part->getPos()->setY(((normalRand(0, 0.5) * bounds->getHeight() / 2.0) + (bounds->getHeight() / 2.0)) - getViewer()->getPos()->getY());
    part->getPos()->setX(((normalRand(0, 0.5) * bounds->getWidth() / 2.0) + (bounds->getWidth() / 2.0)) - getViewer()->getPos()->getX());

    part->getPos()->add(*bounds->getPos());

    particles->push_back(part);
    part->setWorld(this);


  }

  void addType(ParticleType * type) {
    types->push_back(type);
    type->clearTypes();
    for(int j = 0; j < types->size(); j++) {
      ParticleType * other = getType(j);
      type->addType(other);
    }
  }

  void updateTypes() {
    for(int i = 0; i < types->size(); i++) {
      ParticleType * type = getType(i);
      type->clearTypes();
      for(int j = 0; j < types->size(); j++) {
        ParticleType * other = getType(j);
        type->addType(other);
      }
    }
  }

  void createRandomTypes(int n) {
    clearTypes();

    for (int i = 0; i < n; i++) {
      ParticleType * type = new ParticleType();
      types->push_back(type);
    }

    updateTypes();
  }

  void createRandomParts(int n);
  /*{
    clearParts();

    for (int i = 0; i < n; i++) {
      BaseParticle * part = new BaseParticle(this);
      addRandomParticle(part);
    }
  }
  */

  void clearParts() {
    particles->clear();
  }

  void clearTypes() {
    types->clear();
  }

  void clear() {
    clearParts();
    clearTypes();
  }

  void updateBounds() {
    bounds->setPos(getViewer()->getPos());
  }

  void uiReaction() {
    Button * resetButton = ui->getButtonManager()->getButton(0);
    Button * settingsButton = ui->getButtonManager()->getButton(1);
    Button * quitButton = ui->getButtonManager()->getButton(3);

    if(resetButton->isClicked()) {
      initWorld();
      resetButton->reset();
      //std::cout << "reset" << rand() << '\n';
    }

    if(settingsButton->isClicked()) {
      menu->open();
      initWorld();
      //World::update();
      //World::update();
      settingsButton->reset();
      //std::cout << "reset" << rand() << '\n';
    }

    if (quitButton->isClicked()) {
      cont = 0;
      quitButton->reset();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  {
      getViewer()->getPos()->sub(*user->getMouseCursor()->getDiff());
      user->getMouseCursor()->getPos()->sub(*user->getMouseCursor()->getDiff());
    }
  }

  //other

  virtual void start() {}
  virtual void update() {
    World::update();
    ui->update();
    uiReaction();
    user->update();

    for(int i = 0; i < particles->size(); i++){
      getParticle(i)->update();
    }

    updateBounds();
    updateTarget();
  }


  virtual void updateFrame() {
    sf::RenderWindow * window = getViewer()->getWindow();

    window->clear(sf::Color(25, 0, 20));

    getViewer()->update();

    for (int i = 0; i < particles->size(); i++) {
      particles->at(i)->draw();
    }

    ui->draw();

    user->getMouseCursor()->draw();

    window->display();
  }
};
