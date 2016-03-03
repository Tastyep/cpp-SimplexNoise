#ifndef _RENDER_H_
#define _RENDER_H_

#include "NoiseCaller.hh"

#include <SFML/Graphics.hpp>

class Render {
public:
  Render(unsigned int width, unsigned int height);
  virtual ~Render();

  void run();

private:
  void loadNoise(sf::Image &image);
  void handlePressedKey(unsigned int keyCode);

private:
  sf::RenderWindow _window;
  NoiseCaller noise;
  bool refresh;
};

#endif /* _RENDER_H_ */
