#include"../Entity/UserInterface/userInterface.cpp"

class ParticleWorld : public World2D {
private:
  UserInterface * ui;

  vector<BaseParticle*> * particles;
  vector<ParticleType*> * types;

  RectangleEntity * bounds;

  int target = -1;

  int particleAmt = 350;
  int typeAmt = 6;

  void loadAssets() {
    assetManager->loadFile("assests/Fonts/Arial.ttf");
  }

  void initBounds() {
    bounds = new RectangleEntity(100, 100);
    updateBounds();
    bounds->setWidth(getViewer()->getWidth());
    bounds->setHeight(getViewer()->getHeight());
  }

public:
  ParticleWorld() : World2D() {
    ui = new UserInterface(this);
    ui->getButtonManager()->addButton();

    particles = new vector<BaseParticle*>();
    types = new vector<ParticleType*>();

    initBounds();

    setViewer(new Viewer2D());

    initWorld();

    loadAssets();
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
    createRandomTypes(typeAmt);
    createRandomParts(particleAmt);
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

    if(resetButton->isClicked()) {
      initWorld();
      resetButton->reset();
      //std::cout << "reset" << rand() << '\n';
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
