// //
// // Created by sp on 27.04.2025.
// //
//
// #ifndef AVAILABLELEVELOBJECTS_HPP
// #define AVAILABLELEVELOBJECTS_HPP
// #include <vector>
//
// #include "AccelerationField.hpp"
// #include "common.hpp"
// #include "Rectangle.hpp"
// #include "SimulationObjectFactory.hpp"
//
//
// class AvailableLevelObjects {
//
// public:
//     AvailableLevelObjects() {
//         auto* config = new RectanglePhysicsConfig();
//         config->size = {1, 0.1};
//         objects_info.push_back({config, TypeRectangle});
//
//         auto* config2 = new AccelerationFieldPhysicsConfig();
//         config2->size = {0.5, 0.5};
//         config2->force = {0, 5};
//         objects_info.push_back({config2, TypeAccelerationField});
//     }
//
//     struct PhysicsDuo {
//         Drawer* drawer;
//         ObjectPhysics* object;
//     };
//
//     struct PrototypeDuo {
//         Drawer* drawer;
//         ShapePrototype* shape;
//     };
//
//     PhysicsDuo getPhysicsDuo(size_t index, b2WorldId world_id, Vector2D position) {
//         InfoStorage info = objects_info[index];
//         info.config->position = position;
//         ObjectPhysics* obj = SimulationObjectFactory::createObjectPhysics(info.type, info.config, world_id);
//         Drawer* drawer = SimulationObjectFactory::createObjectDrawer(info.type, obj);
//         return {drawer, obj};
//     }
//
//     PhysicsDuo getPhysicsDuo(size_t index, b2WorldId world_id, Vector2D position, float rotation) {
//         InfoStorage info = objects_info[index];
//         info.config->position = position;
//         info.config->rotation = rotation;
//         ObjectPhysics* obj = SimulationObjectFactory::createObjectPhysics(info.type, info.config, world_id);
//         Drawer* drawer = SimulationObjectFactory::createObjectDrawer(info.type, obj);
//         return {drawer, obj};
//     }
//
//
//     PrototypeDuo getPrototypeDuo(size_t index) {
//         InfoStorage info = objects_info[index];
//         ShapePrototype* shape = SimulationObjectFactory::createObjectPrototype(info.type, info.config);
//         Drawer* drawer = SimulationObjectFactory::createObjectDrawer(info.type, shape);
//         return {drawer, shape};
//     }
//
//     size_t getSize() {
//         return this->objects_info.size();
//     }
//
//
// private:
//     struct InfoStorage {
//         ObjectPhysicsConfig* config;
//         PhysicsObjectType type;
//     };
//     std::vector<InfoStorage> objects_info;
// };
//
//
//
// #endif //AVAILABLELEVELOBJECTS_HPP
