#include "Render.hh"

#include <iostream>

Render::Render(unsigned int width, unsigned int height)
    : _window(sf::VideoMode(width, height), "Noise Renderer"), refresh(true) {}

Render::~Render() {}

void Render::loadNoise(sf::Image &image) {
  sf::Vector2u size = image.getSize();
  float value;
  sf::Color color;

  for (unsigned int y = 0; y < size.y; ++y) {
    for (unsigned int x = 0; x < size.x; ++x) {
      // float x, float y, int octaves = 2, float scale = 1,
      // float lacunarity = 1, float gain = 0.5
      value = noise.call(x, y, 8, 0.008, 2.5, 0.3);
      color =
          sf::Color(127 + 127 * value, 127 + 127 * value, 127 + 127 * value);
      image.setPixel(x, y, color);
    }
  }
}

void Render::handlePressedKey(unsigned int keyCode) {
  switch (keyCode) {
  case sf::Keyboard::Up:
    this->noise.setIdx(this->noise.getIdx() - 1);
    this->refresh = true;
    break;
  case sf::Keyboard::Down:
    this->noise.setIdx(this->noise.getIdx() + 1);
    this->refresh = true;
    break;
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

  _window.setFramerateLimit(25);

  while (_window.isOpen()) {
    _window.clear();
    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        _window.close();
      else if (event.type == sf::Event::KeyPressed) {
        this->handlePressedKey(event.key.code);
      }
    }
    if (this->refresh) {
      loadNoise(image);
      texture.update(image);
      sprite.setTexture(texture);
      this->refresh = false;
    }
    _window.draw(sprite);
    _window.display();
  }
}
