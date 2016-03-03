#include "Render.hh"

#include <iostream>

Render::Render(unsigned int width, unsigned int height)
    : _window(sf::VideoMode(width, height), "Noise Renderer") {}

Render::~Render() {}

void Render::loadNoise(sf::Image &image) {
  sf::Vector2u size = image.getSize();
  float value;
  sf::Color color;

  for (unsigned int y = 0; y < size.y; ++y) {
    for (unsigned int x = 0; x < size.x; ++x) {
      value = noise.fbm(x, y, 2, 0.01);
      color =
          sf::Color(127 + 127 * value, 127 + 127 * value, 127 + 127 * value);
      image.setPixel(x, y, color);
    }
  }
}

void Render::run() {
  sf::Event event;
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2u size = _window.getSize();

  image.create(size.x, size.y, sf::Color::Black);
  texture.create(size.x, size.y);

  _window.setFramerateLimit(1);

  while (_window.isOpen()) {
    _window.clear();
    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        _window.close();
    }
    loadNoise(image);
    texture.update(image);
    sprite.setTexture(texture);
    _window.draw(sprite);
    _window.display();
  }
}
