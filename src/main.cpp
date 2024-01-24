#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <iostream>

class AShape
{
public:
  std::shared_ptr<sf::Shape> shape;
  float speedX, speedY;
  sf::Text text;
  AShape(std::shared_ptr<sf::Shape> shape, float speedX, float speedY, sf::Text& text)
    : shape(shape)
    , speedX(speedX)
    , speedY(speedY)
    , text(text)
  {}
};

int main(int argc, char* argv[]) {
  std::vector<std::shared_ptr<AShape>> shapes;
  std::ifstream fin("config.txt");
  int wWidth;
  int wHeight;
  std::string fontPath;
  int fontSize;
  int fontR;
  int fontG;
  int fontB;
  std::string type;
  std::string shapeName;
  int shapeX;
  int shapeY;
  float shapeSpeedX;
  float shapeSpeedY;
  int shapeR;
  int shapeG;
  int shapeB;
  int shapeSizeX;
  int shapeSizeY;
  int shapeRadius;
  sf::Font myFont;



  while (fin >> type) {
    if (type == "Window") {
      fin >> wWidth >> wHeight;
      continue;
    }

    if (type == "Font") {
      fin >> fontPath >> fontSize >> fontR >> fontG >> fontB;
      if (!myFont.loadFromFile(fontPath)) {
        std::cerr << "Could not load font!\n";
        exit(-1);
      }
      continue;
    }

    if (type == "Circle") {
      fin >> shapeName >> shapeX >> shapeY >> shapeSpeedX >> shapeSpeedY >> shapeR >> shapeG >> shapeB >> shapeRadius;
      std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(shapeRadius);
      sf::Text text(shapeName, myFont, fontSize);
      text.setFillColor(sf::Color(fontR, fontG, fontB));
      circle->setPosition(shapeX, shapeY);
      circle->setFillColor(sf::Color(shapeR, shapeG, shapeB));
      std::shared_ptr<AShape> shape = std::make_shared<AShape>(circle, shapeSpeedX, shapeSpeedY, text);
      shapes.push_back(shape);
      continue;
    }

    if (type == "Rectangle") {
      fin >> shapeName >> shapeX >> shapeY >> shapeSpeedX >> shapeSpeedY >> shapeR >> shapeG >> shapeB >> shapeSizeX >> shapeSizeY;
      sf::Vector2f rSize(shapeSizeX, shapeSizeY);
      std::shared_ptr<sf::Shape> rect = std::make_shared<sf::RectangleShape>(rSize);
      sf::Text text(shapeName, myFont, fontSize);
      text.setFillColor(sf::Color(fontR, fontG, fontB));
      rect->setPosition(shapeX, shapeY);
      rect->setFillColor(sf::Color(shapeR, shapeG, shapeB));
      std::shared_ptr<AShape> shape = std::make_shared<AShape>(rect, shapeSpeedX, shapeSpeedY, text);
      shapes.push_back(shape);
      continue;
    }
  }

  sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML Assignment");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    for (auto& shape : shapes) {
      if (shape->shape->getPosition().x <= 0 || shape->shape->getPosition().x >= wWidth - shape->shape->getGlobalBounds().width) shape->speedX = -shape->speedX;
      if (shape->shape->getPosition().y <= 0 || shape->shape->getPosition().y >= wHeight - shape->shape->getGlobalBounds().height) shape->speedY = -shape->speedY;
      shape->shape->setPosition(shape->shape->getPosition().x + shape->speedX * 10, shape->shape->getPosition().y + shape->speedY * 10);
      shape->text.setPosition(shape->shape->getPosition().x + (shape->shape->getGlobalBounds().width - shape->text.getGlobalBounds().width) / 2, shape->shape->getPosition().y + (shape->shape->getGlobalBounds().height - shape->text.getGlobalBounds().height) / 2);
      window.draw(*shape->shape);
      window.draw(shape->text);
    }

    window.display();
  }
}