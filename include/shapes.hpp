#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "graphics.hpp"
#include "vec2.hpp"
#include <string>

// class Graphics;

class Shape {
protected:
  vec2 position;
  char *texture;

public:
  Shape(vec2 position, char *texture);

  virtual char *draw(Graphics *graphics);

  void move(vec2 direction);

  void setPosition(vec2 newPosition);

  vec2 getPosition();
};

class Circle : public Shape {
protected:
  float size;

public:
  Circle(vec2 position, float size, char *texture);

  char *draw(Graphics *graphics);
};

class Line : public Shape {
protected:
  vec2 endPosition;
  float k, a;

public:
  Line(vec2 position, vec2 endPosition, char *texture);

  char *draw(Graphics *graphics);
};

class SolidRectangle : public Shape {
protected:
  vec2 size;

public:
  SolidRectangle(vec2 position, vec2 size, char *texture);

  char *draw(Graphics *graphics);
};

class Text : public Shape {
protected:
  std::string content;

public:
  Text(vec2 position, std::string content);

  char *draw(Graphics *graphics);
};

#endif
