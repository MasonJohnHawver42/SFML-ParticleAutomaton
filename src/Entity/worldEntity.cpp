#include "../World/particleWorld.cpp"

class WorldEntity {
protected:
  ParticleWorld * basicWorld;

public:
  WorldEntity(ParticleWorld * wrld) { basicWorld = wrld; }
  WorldEntity() { basicWorld = nullptr; }

  //getters

  ParticleWorld * getBasicWorld() { return basicWorld; }

  //setters

  virtual void setBasicWorld(ParticleWorld * wrld) {
    basicWorld = wrld;
  }
};
