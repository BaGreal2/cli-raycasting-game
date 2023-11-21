#include "../include/shapes.hpp"
#include "../include/graphics.hpp"
#include "../include/vec2.hpp"

Shape::Shape(vec2 position, char *texture) : position(position) {
  this->position = position;
  this->texture = texture;
}

char *Shape::draw(Graphics *graphics) {
  return new char[graphics->width * graphics->height];
}

void Shape::move(vec2 direction) { position = position + direction; }

void Shape::setPosition(vec2 newPosition) { position = newPosition; }

vec2 Shape::getPosition() { return position; }

Circle::Circle(vec2 position, float size, char *texture)
    : Shape(position, texture) {
  this->size = size;
}

char *Circle::draw(Graphics *graphics) {
  char *buffer = new char[graphics->width * graphics->height];
  for (int i = 0; i < graphics->width; ++i) {
    for (int j = 0; j < graphics->height; ++j) {
      float x = (float)i / graphics->width * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      float y = (float)j / graphics->height * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      x *= graphics->aspect * graphics->pixelAspect;
      float f = (x - position.x) * (x - position.x) +
                (y - position.y) * (y - position.y);

      char pixel;

      if (f < size) {
        if (f < size / 8)
          pixel = texture[3];
        else if (f < size / 3)
          pixel = texture[2];
        else if (f < size / 1.5f)
          pixel = texture[1];
        else
          pixel = texture[0];

        buffer[i + j * graphics->width] = pixel;
      }
    }
  }
  return buffer;
}

Line::Line(vec2 position, vec2 endPosition, char *texture)
    : Shape(position, texture), endPosition(endPosition) {
  k = (endPosition.y - position.y) / (endPosition.x - position.x);
  a = position.y - position.x * k;
}

char *Line::draw(Graphics *graphics) {
  char *buffer = graphics->buffer;
  for (int i = 0; i < graphics->width; i++) {
    for (int j = 0; j < graphics->height; j++) {
      float x = (float)i / graphics->width * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      float y = (float)j / graphics->height * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      x *= graphics->aspect * graphics->pixelAspect;
      float f = k * x + a;
      if (y > f - 0.05f && y < f + 0.05f && x > position.x && x < endPosition.x)
        buffer[i + j * graphics->width] = texture[0];
    }
  }
  return buffer;
}

SolidRectangle::SolidRectangle(vec2 position, vec2 size, char *texture)
    : Shape(position, texture), size(size){};

char *SolidRectangle::draw(Graphics *graphics) {
  char *buffer = graphics->buffer;
  for (int i = 0; i < graphics->width; ++i) {
    for (int j = 0; j < graphics->height; ++j) {
      float x = (float)i / graphics->width * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      float y = (float)j / graphics->height * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      x *= graphics->aspect * graphics->pixelAspect;

      if (x > position.x && x < position.x + size.x && y > position.y &&
          y < position.y + size.y)
        buffer[i + j * graphics->width] = texture[0];
    }
  }
  return buffer;
}

Text::Text(vec2 position, std::string content) : Shape(position, new char[]{' '}) {
  this->content = content;
}

char *Text::draw(Graphics *graphics) {
  char *buffer = graphics->buffer;
  bool drawed = false;
  for (int i = 0; i < graphics->width; ++i) {
    for (int j = 0; j < graphics->height; ++j) {
      float x = (float)i / graphics->width * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      float y = (float)j / graphics->height * 2.0f * graphics->multiplier -
                1.0f * graphics->multiplier;
      x *= graphics->aspect * graphics->pixelAspect;

      if (x >= position.x && x <= position.x + content.size() &&
          y >= position.y && y <= position.y + 1) {
        for (int k = i + j * graphics->width;
             k < i + j * graphics->width + content.size(); ++k) {
          buffer[k] = content.at(k - (i + j * graphics->width));
        }
        drawed = true;
      }
      if (drawed)
        break;
      if (drawed)
        break;
    }
  }
  return buffer;
}
