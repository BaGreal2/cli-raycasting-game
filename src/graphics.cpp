#include "../include/graphics.hpp"
#include "../include/shapes.hpp"
#include <ncurses.h>

Graphics::Graphics(int width, int height, float multiplier) {
  this->width = width;
  this->height = height;
  this->multiplier = multiplier;
  aspect = (float)width / height;
  pixelAspect = 11.0f / 23.0f;
  buffer = new char[width * height];
}

void Graphics::reset() {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      buffer[i + j * width] = ' ';
    }
  }
}

void Graphics::begin() {
  reset();
  refresh();
}

void Graphics::draw(Shape &shape) {
  char *shapeBuffer = shape.draw(this);
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; j++) {
      if (shapeBuffer[i + j * width] != 0)
        buffer[i + j * width] = shapeBuffer[i + j * width];
    }
  }
}

void Graphics::end() {
  bool underlineMode = false;
  bool boldMode = false;
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      int index = row * width + col;
      char ch = buffer[index];

      if (ch == '_' && !underlineMode) {
        underlineMode = true;
        mvaddch(row, col, ' ');
        attron(A_UNDERLINE);
      } else if (ch == '_' && underlineMode) {
        underlineMode = false;
        attroff(A_UNDERLINE);
        mvaddch(row, col, ' ');
      } else if (ch == '.' && !boldMode) {
        boldMode = true;
        mvaddch(row, col, ' ');
        attron(A_BOLD);
      } else if (ch == '.' && boldMode) {
        boldMode = false;
        attroff(A_BOLD);
        mvaddch(row, col, ' ');
      } else {
        mvaddch(row, col, ch);
      }
    }
  }
  refresh();
}
