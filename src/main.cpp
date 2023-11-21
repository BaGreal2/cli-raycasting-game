#include "../include/graphics.hpp"
#include "../include/shapes.hpp"
#include "../include/vec2.hpp"
#include <iostream>
#include <locale.h>
#include <memory>
#include <ncurses.h>
#include <random>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>
#include <vector>

using std::vector;

int main() {
  setlocale(LC_ALL, "");
  initscr();
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width = w.ws_col;
  int height = w.ws_row;

  Graphics graphics(width, height, 2);
  SolidRectangle smth(vec2(-2.5f, 0.5f), vec2(5.0f, 0.5f), new char[]{'/'});

  vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<SolidRectangle>(
      vec2(-2.5f, 0.5f), vec2(5.0f, 0.5f), new char[]{'/'}));
  shapes.push_back(std::make_unique<SolidRectangle>(
      vec2(-0.2f, 0.4f), vec2(0.4f, 0.5f), new char[]{'o'}));
  shapes.push_back(std::make_unique<Line>(vec2(-0.7f, 0.4f), vec2(-0.2f, -0.2f),
                                          new char[]{'/'}));
  shapes.push_back(std::make_unique<Line>(vec2(0.2f, -0.2f), vec2(0.7f, 0.4f),
                                          new char[]{'\\'}));
  shapes.push_back(std::make_unique<Line>(vec2(-0.7f, 0.4f), vec2(0.7f, 0.4f),
                                          new char[]{'='}));
  shapes.push_back(std::make_unique<Line>(vec2(-0.45f, -0.25f),
                                          vec2(-0.1f, -0.7f), new char[]{'/'}));
  shapes.push_back(std::make_unique<Line>(
      vec2(0.1f, -0.7f), vec2(0.45f, -0.25f), new char[]{'\\'}));
  shapes.push_back(std::make_unique<Line>(
      vec2(-0.45f, -0.25f), vec2(0.45f, -0.25f), new char[]{'='}));
  shapes.push_back(std::make_unique<Line>(vec2(-0.3f, -0.7f), vec2(0.0f, -1.1f),
                                          new char[]{'/'}));
  shapes.push_back(std::make_unique<Line>(vec2(0.0f, -1.1f), vec2(0.3f, -0.7f),
                                          new char[]{'\\'}));
  shapes.push_back(std::make_unique<Line>(vec2(-0.3f, -0.7f), vec2(0.3f, -0.7f),
                                          new char[]{'='}));
  shapes.push_back(std::make_unique<Circle>(vec2(-0.3f, 0.0f), 0.02f,
                                            new char[]{'.', ':', 'a', '@'}));
  shapes.push_back(std::make_unique<Circle>(vec2(0.4f, 0.2f), 0.02f,
                                            new char[]{'.', ':', 'a', '@'}));
  shapes.push_back(std::make_unique<Circle>(vec2(0.1f, -0.2f), 0.02f,
                                            new char[]{'.', ':', 'a', '@'}));
  shapes.push_back(std::make_unique<Circle>(vec2(-0.1f, -0.5f), 0.02f,
                                            new char[]{'.', ':', 'a', '@'}));
  shapes.push_back(std::make_unique<Circle>(vec2(0.0f, -1.1f), 0.05f,
                                            new char[]{'.', ':', 'a', '@'}));

  vector<std::unique_ptr<Shape>> snowflakes;
  std::random_device rd;
  for (int i = 0; i < 20; ++i)
    snowflakes.push_back(std::make_unique<Circle>(
        vec2(-1.5f + std::generate_canonical<float, 10>(rd) * 4.5f,
             -1.0f - std::generate_canonical<float, 10>(rd) * 2.5f),
        0.002f, new char[]{'*', '*', '*', '*'}));

  Text someText(vec2(-1.2f, -1.2f), "_Underscored_");
  Text someBoldText(vec2(-1.2f, -1.0f), "$Bold text$");

  while (true) {
    graphics.begin();

    for (const auto &shape : shapes) {
      graphics.draw(*shape.get());
    }

    for (const auto &s : snowflakes) {
      graphics.draw(*s.get());
      s->move(vec2(-0.005f, 0.01f));
      if (s->getPosition().y > 1) {
        s->setPosition(
            vec2(-1.5f + std::generate_canonical<float, 10>(rd) * 4.5f,
                 -1.0f - std::generate_canonical<float, 10>(rd) * 2.5f));
      }
    }

    graphics.end();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  getchar();
  endwin();
  return 0;
}
