#include"worldEntity.cpp"

class Particle : public WorldEntity, public BaseParticle {
public:
  Particle(ParticleWorld * world, ParticleType * type) : WorldEntity(world), BaseParticle(world, type) {
  }
  Particle(ParticleWorld * world) : WorldEntity(world), BaseParticle(world) {
  }

  virtual void update() {

    for (int i = 0; i < basicWorld->getParticleAmt(); i++) {
      BaseParticle * part = basicWorld->getParticle(i);
      if(!BaseParticle::equal(part)) {
             applyAtraction(part, basicWorld->getBounds());
      }

  //    if(!basicWorld->getBounds()->isInside(pos)) {
        //std::cout << rand() << '\n';
    //  }
    }

    PhysicsBasedEntity::update();

    if(warpedBounds ) { applyWarpedBounds(basicWorld->getBounds()); }
    else if(circleBounds ) { applyCircleBounds(basicWorld->getBounds());  }
    else { applyBounds(basicWorld->getBounds()); }

  }
};


void ParticleWorld::createRandomParts(int n) {
  clearParts();

  for (int i = 0; i < n; i++) {
    Particle * part = new Particle(this);
    addRandomParticle(part);
  }
}

void addRandomParticles(ParticleWorld * world, int n) {
  world->clearParts();

  for (int i = 0; i < n; i++) {
    Particle * part = new Particle(world);
    world->addRandomParticle(part);
  }
}
