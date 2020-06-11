#include "assetLoader.cpp"


class FontLoader : public AssetLoader<sf::Font> {
public:
 FontLoader() : AssetLoader() {}

 virtual std::string getFileFormat() {
   return "ttf";
 }

 virtual void loadAsset(string fileName) {
   if(correctFormat(fileName)) {
     files->push_back(fileName);

     sf::Font * font = new sf::Font();
     font->loadFromFile(fileName);
     assets->push_back(font);
   }
 }
};
