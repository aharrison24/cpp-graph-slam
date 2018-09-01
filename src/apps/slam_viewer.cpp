#include <SFML/Graphics.hpp>

constexpr int window_width = 1024;
constexpr int window_height = 768;

class Viewer {
public:
  Viewer() {
    window_.setFramerateLimit(60);
  }

  void run() {
    while (window_.isOpen()) {
      auto event = sf::Event();
      while (window_.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window_.close();
        }

        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Escape) {
            window_.close();
          };
        }
      }

      // clear the window with black color
      window_.clear(sf::Color::Black);

      // draw everything here...
      // window.draw(...);

      // end the current frame
      window_.display();
    }
  }

private:
  sf::RenderWindow window_ = {{window_width, window_height}, "SLAM Viewer"};
};

int main() {
  Viewer viewer;
  viewer.run();
}
