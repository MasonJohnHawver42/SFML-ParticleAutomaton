#include "../Entity/particle.cpp"

int a  = 0;

void play() {

  atractionMean = -2;
  atractionSTD = 4;

  repultionMean = 2;
  repultionSTD = 10;

  minReachLower = 2;
  minReachUpper = 8;

  maxReachLower = 10;
  maxReachUpper = 20;

  warpedBounds = 1;
  circleBounds = 0;

  gFriction = .7;  //.7


  srand (time(NULL));

  ParticleWorld * world = new ParticleWorld();
  //world->createRandomTypes(6);
  //world->createRandomParts(250);
  //world->setTarget(10);

  double fps = 140.0;

  sf::Clock * clock = new sf::Clock();

  while (1){

    if(clock->getElapsedTime().asSeconds() > 1. / fps) {
      world->updateFrame();
      clock->restart();
    }

    world->update();

  }

  return;
}
