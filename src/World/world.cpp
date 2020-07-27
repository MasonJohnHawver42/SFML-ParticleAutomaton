#include "../UserControl/user.cpp"

class World {
protected:

  int id;
  int static next_id;

  bool cont = 1;

  AssetManager * assetManager;

  sf::Clock * masterClock;

private:

  double updateTimeDelta = 0;

public:

  World() {
    assetManager = new AssetManager();
    masterClock = new sf::Clock();

    id = next_id;
    next_id++;
  }

  //getters

  int getId() { return id; }

  double getUpdateTimeDelta() { return updateTimeDelta; }

  AssetManager * getAssetMng() { return assetManager; }

  //setters

  //virtuals

  virtual void start() {}
  virtual bool continueGame() { return cont; }
  virtual void update() { updateTimeDelta = masterClock->restart().asSeconds() * 10; }
  virtual void updateFrame() {}

  virtual bool equal(World other) {
    return (id == other.getId());
  }

};

int World::next_id = 0;
