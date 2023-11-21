#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <ncurses.h>

class Shape;

class Graphics {
public:
  int width, height;
  float aspect, pixelAspect, multiplier;
  char *buffer;

  Graphics(int width, int height, float multiplier);

  void reset();

  void begin();

  void draw(Shape &shape);

  void end();
};

#endif
