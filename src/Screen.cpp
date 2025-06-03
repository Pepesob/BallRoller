#include "Screen.hpp"

#include <iostream>

void debug_lines(sf::RenderWindow *window) {
    // Calculate 10% of window dimensions
    float cellWidth = window->getSize().x * 0.05f;
    float cellHeight = window->getSize().y * 0.05f;


    sf::Vertex line[2];
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    // Draw vertical lines
    for (float x = cellWidth; x < window->getSize().x; x += cellWidth)
    {
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, window->getSize().y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Draw horizontal lines
    for (float y = cellHeight; y < window->getSize().y; y += cellHeight)
    {
        line[0].position = sf::Vector2f(0, y);
        line[1].position = sf::Vector2f(window->getSize().x, y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Create a red dot at the center of the screen
    sf::CircleShape redDot(5); // Radius 10
    redDot.setFillColor(sf::Color::Cyan);

    // Position the dot at the center of the window
    redDot.setPosition({window->getSize().x / 2 - redDot.getRadius(), window->getSize().y / 2 - redDot.getRadius()});

    // Draw the red dot
    window->draw(redDot);
}

Screen::Screen(unsigned int width, unsigned int height): background_texture("resources/background_texture.jpg"), background(this->background_texture) {
    this->width = width;
    this->height = height;
    this->window = nullptr;
    this->pixel_scale_factor = height/2;
    this->needs_update = true;
    this->window_name = "BallRoller";
}

Screen::~Screen() {
    delete this->window;
}

void Screen::createWindow() {
    if (this->window == nullptr) {
        this->window = new sf::RenderWindow();
        this->window->create(sf::VideoMode({this->width, this->height}), this->window_name);
    }
    else {
        throw std::runtime_error("Window already exists");
    }
}

void Screen::destroyWindow() {
    if (this->window != nullptr) {
        this->window->close();
        delete this->window;
        this->window = nullptr;
    }
    else {
        throw std::runtime_error("Window does not exist");
    }
}

void Screen::handleWindowEvents() {
    if (this->window == nullptr) {
        throw std::runtime_error("Window does not exist");
    }
    while (const std::optional event = this->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            std::exit(EXIT_SUCCESS);
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            this->setSize(resized->size.x, resized->size.y);
        }
    }
}

void Screen::handleEvent(const std::optional<sf::Event>& event) {
    if (event->is<sf::Event::Closed>()) {
        this->destroyWindow();
        std::exit(0);
    }
    else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
        this->setSize(resized->size.x, resized->size.y);
    }
    // else if (const auto* pressed = event->getIf<sf::Event::KeyPressed>()) {
    //     if (pressed->code == sf::Keyboard::Key::Escape) {
    //     }
    // }
}

sf::Transform & Screen::getScreenMatrix() {
    if (this->needs_update) {
        this->updateScreenMatrix();
    }
    return this->screen_matrix;
}

unsigned int Screen::getWidth() const {
    return this->width;
}

unsigned int Screen::getHeight() const {
    return this->height;
}

void Screen::updateScreenMatrix() {
    float w = this->width;
    float h = this->height;
    this->screen_matrix = sf::Transform(
        w / 2.f, 0, w/ 2.f,
        0, -h / 2.f, h / 2.f,
        0, 0, 1
    );
    needs_update = false;
}

void Screen::setSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    if (this->window != nullptr) {
        this->window->setSize({this->width, this->height});
        sf::View v(sf::FloatRect({0.f, 0.f}, {static_cast<float>(this->width), static_cast<float>(this->height)}));
        this->window->setView(v);
        this->pixel_scale_factor = this->height/2;
    }
    needs_update = true;
}

int Screen::getPixelScaleFactor() const {
    return this->pixel_scale_factor;
}

sf::RenderWindow* Screen::getWindow() const {
    return this->window;
}

bool Screen::isWindowOpen() const {
    return this->window != nullptr;
}

void Screen::draw(Screen *screen, Camera *camera) {
    Vector2D v_cam = camera->getPosition();
    sf::Vector2f v = screen->getScreenMatrix().transformPoint({v_cam.x, v_cam.y});
    sf::Vector2f v_background = (sf::Vector2f(this->background_texture.getSize()) / 4.f + v);
    this->background.setPosition(-v_background);
    screen->getWindow()->draw(this->background);
}
