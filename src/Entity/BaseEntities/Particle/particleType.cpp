#include "../circleEntity.cpp"
#include <time.h>
#include <chrono>
#include <random>

double normalRand(double m, double s) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::normal_distribution<double> distribution (m, s);
  return distribution(generator);
}
double uniRand(double m1, double m2) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::uniform_real_distribution<double> distribution (m1, m2);
  return distribution(generator);
}

double atractionMean = 0;
double atractionSTD = 0;

double repultionMean = 0;
double repultionSTD = 0;

double minReachLower = 0;
double minReachUpper = 0;

double maxReachLower = 0;
double maxReachUpper = 0;


class ParticleType {
private:
  std::vector<ParticleType*> * types;
  std::vector<double> * atractions; // -inf , inf
  std::vector<double> * repultions; // 0 <

  std::vector<double> * minReach; // 0 <
  std::vector<double> * maxReach; // minReach <

  sf::Color * color;

  int id;
  static int nextId;

  void setRandomColor() {
    int range = 150;

    color->r = (255 - range) + (rand() % range);
    color->g = (255 - range) + (rand() % range);
    color->b = (255 - range) + (rand() % range);
  }

  void addRandomAtributes() {
    atractions->push_back(normalRand(atractionMean, atractionSTD));
    repultions->push_back(abs(normalRand(repultionMean, repultionSTD)));
    minReach->push_back(uniRand(minReachLower, minReachUpper));
    maxReach->push_back(uniRand(maxReachLower, maxReachUpper));
  }

public:
  ParticleType() {
    types = new vector<ParticleType*>();
    atractions = new vector<double>();
    repultions = new vector<double>();

    minReach = new vector<double>();
    maxReach = new vector<double>();

    color = new sf::Color();
    setRandomColor();

    id = nextId;
    nextId++;
  }

  ~ ParticleType() {
    delete types;
    delete atractions, repultions;
    delete minReach, maxReach;

    delete color;
  }

  //getters

  int getid() { return id; }

  int getIndex(ParticleType * type) {
    for(int i = 0; i < atractions->size(); i++) {
      if(types->at(i)->equal(type)) {
        return i;
      }
    }

    if(equal(type)) { std::cout << "here" << '\n';}

    return -1;
  }

  double getAtraction(int i) { return atractions->at(i); }
  double getRepultion(int i) { return repultions->at(i); }
  double getMinReach(int i) { return minReach->at(i); }
  double getMaxReach(int i) { return maxReach->at(i); }

  sf::Color * getColor() { return color; }

  //setters

  void setAtraction(int index, double a) { atractions->at(index) = a; }
  void setRepultion(int i, double a) { repultions->at(i) = a; }
  void setMinReach(int index, double a) { minReach->at(index) = a; }
  void setMaxReach(int index, double a) { maxReach->at(index) = a; }

  void setRandomAtributes() {
    clearInteractions();

    for(int i = 0; i < types->size(); i++ ) {
      addRandomAtributes();
    }
  }

  //modders

  void addType(ParticleType * type) {
    types->push_back(type);
    addRandomAtributes();
  }

  void clearTypes() {
    types->clear();
  }

  void clearInteractions() {
    atractions->clear();
    repultions->clear();
    minReach->clear();
    maxReach->clear();
  }

  //checkers

  bool equal(ParticleType * type) {
    return id == type->getid();
  }

};
int ParticleType::nextId = 0;
