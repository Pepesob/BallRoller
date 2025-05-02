// //
// // Created by sp on 26.04.2025.
// //
//
// #ifndef OBJECTPLACEMENTSTAGE_HPP
// #define OBJECTPLACEMENTSTAGE_HPP
// #include "AvailableLevelObjects.hpp"
// #include "DrawingEngine.hpp"
// #include "Drawer.hpp"
// #include "Rectangle.hpp"
// #include "Shape.hpp"
// #include "SimulationObjectFactory.hpp"
// #include "physics/ObjectPhysics.hpp"
// #include "physics/PhysicsEngine.hpp"
// #include "SFML/Window.hpp"
//
//
// class ObjectPlacementStage {
//
// public:
//     ObjectPlacementStage(PhysicsEngine* physics_engine, DrawingEngine* drawing_engine, Screen* screen, Camera* camera) {
//         this->physics_engine = physics_engine;
//         this->drawing_engine = drawing_engine;
//         this->screen = screen;
//         this->camera = camera;
//
//         SimulationShape* shape = new RectangleShape({1, 0.1});
//         SimulationBody* body = new SimulationBody();
//         body->addShape(shape);
//
//         this->available_objects[0] = new SimulationObject();
//         this->available_objects[0]->addBody(body);
//
//     }
//
//     void keyboardInput() {
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
//             this->index = 0;
//             // auto [drawer, shape] = this->available_level_objects.getPrototypeDuo(this->index);
//             // this->current_prototype = shape;
//             // this->current_drawer = drawer;
//             this->current_object = new SimulationObject();
//             // this->
//         }
//         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
//             // this->index = 1;
//             // auto [drawer, shape] = this->available_level_objects.getPrototypeDuo(this->index);
//             // this->current_prototype = shape;
//             // this->current_drawer = drawer;
//         }
//         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
//             this->current_prototype = nullptr;
//             this->current_drawer = nullptr;
//         }
//         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
//             sf::Transform t = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse();
//             sf::Vector2f current = t.transformPoint(sf::Vector2f(sf::Mouse::getPosition(*this->screen->getWindow())));
//             sf::Vector2f prev = t.transformPoint(sf::Vector2f(this->mouse_pos));
//             sf::Vector2f dx = prev - current;
//             this->camera->move(dx.x, dx.y);
//         }
//         this->mouse_pos = sf::Mouse::getPosition(*this->screen->getWindow());
//         this->world_pos = (screen->getScreenMatrix() * camera->getCameraMatrix()).getInverse().transformPoint(sf::Vector2f(this->mouse_pos));
//         if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
//             this->placeObject();
//             pressed = true;
//         } else {
//             pressed = false;
//         }
//     }
//
//     void placeObject() {
//         if (pressed == true) {
//             return;
//         }
//         auto [drawer, obj] = this->available_level_objects.getPhysicsDuo(this->index, this->physics_engine->getWorldId(), {this->world_pos.x, this->world_pos.y});
//         this->physics_engine->addObjectPhysics(obj);
//         this->drawing_engine->addDrawer(drawer);
//     }
//
//     void draw(Screen* screen, Camera* camera) {
//         if (this->current_drawer != nullptr) {
//             this->current_prototype->setPosition({this->world_pos.x, this->world_pos.y});
//             this->current_drawer->draw(screen, camera);
//         }
//     }
//
// private:
//     bool pressed = false;
//     size_t index = -1;
//     AvailableLevelObjects available_level_objects;
//     PhysicsEngine* physics_engine;
//     DrawingEngine* drawing_engine;
//     Screen* screen;
//     Camera* camera;
//     sf::Vector2i mouse_pos;
//     sf::Vector2f world_pos;
//     Drawer* current_drawer = nullptr;
//     ObjectPhysicsConfig* current_config = nullptr;
//     ShapePrototype* current_prototype = nullptr;
//     SimulationObject* current_object = nullptr;
//
//     SimulationObject* available_objects[4];
// };
//
//
//
// #endif //OBJECTPLACEMENTSTAGE_HPP
