#include <SFML/Graphics.hpp>

constexpr int default_window_width = 1024;
constexpr int default_window_height = 768;

constexpr int pixels_per_meter = 60;

namespace {
class Grid : public sf::Drawable {
public:
  Grid(std::size_t rows, std::size_t cols, float col_width, float row_height) {
    sf::Color const color(255, 255, 255, 75);

    float const half_width = (cols * col_width) / 2.f;
    float const half_height = (rows * row_height) / 2.f;

    vertices_.reserve(2 * (rows + cols + 2));

    for (std::size_t i = 0; i < rows + 1; ++i) {
      float const y = -half_height + i * col_width;
      vertices_.emplace_back(sf::Vector2f(-half_width, y), color);
      vertices_.emplace_back(sf::Vector2f(half_width, y), color);
    }

    for (std::size_t j = 0; j < cols + 1; ++j) {
      float const x = -half_width + j * row_height;
      vertices_.emplace_back(sf::Vector2f(x, -half_height), color);
      vertices_.emplace_back(sf::Vector2f(x, half_height), color);
    }
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(&vertices_[0], vertices_.size(), sf::Lines, states);
  }

private:
  std::vector<sf::Vertex> vertices_;
};

class Robot : public sf::Drawable {
public:
  Robot() {
    vertices_ = {sf::Vertex({0.5, 0}, sf::Color::White),
                 sf::Vertex({-0.5, 0.25}, sf::Color::White),
                 sf::Vertex({-0.5, -0.25}, sf::Color::White)};
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(&vertices_[0], vertices_.size(), sf::Triangles, states);
  }

private:
  std::vector<sf::Vertex> vertices_;
};

class Viewer {
public:
  Viewer() : grid_(1000, 1000, 1, 1) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window_.create({default_window_width, default_window_height}, "SLAM Viewer",
                   sf::Style::Default, settings);

    window_.setFramerateLimit(60);

    updateViewport();
  }

  void updateViewport() {
    auto const viewport_width = window_.getSize().x / pixels_per_meter;
    auto const viewport_height = window_.getSize().y / pixels_per_meter;

    sf::Vector2f const center(0.f, 0.f);
    sf::Vector2f const size(viewport_width, viewport_height);
    sf::View const view(center, size);
    window_.setView(view);
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

        if (event.type == sf::Event::Resized) {
          updateViewport();
        }
      }

      // clear the window with black color
      window_.clear(sf::Color::Black);

      // draw everything here...
      window_.draw(grid_);
      window_.draw(robot_);

      // end the current frame
      window_.display();
    }
  }

private:
  sf::RenderWindow window_;

  Grid grid_;
  Robot robot_;
};
} // namespace

int main() {
  Viewer viewer;
  viewer.run();
}
