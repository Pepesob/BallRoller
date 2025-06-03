#include "Gameloop.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Screen.hpp"
#include "stage/ObjectPlacementStage.hpp"
#include "LevelSetup.hpp"
#include "stage/MainMenuStage.hpp"


void gameloop() {
    // register_sprites();

    Screen screen(720, 720);
    Camera camera(0,0,0.3);
    // StateMachine state_machine(std::make_unique<MainMenuStage>(state_machine, &screen, &camera));

    screen.createWindow();

    auto prev_time = std::chrono::steady_clock::now();

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0, -6.0};
    b2WorldId world_id = b2CreateWorld(&worldDef);

    b2BodyDef rect_body_def = b2DefaultBodyDef();
    rect_body_def.type = b2_dynamicBody;
    b2BodyId rect_body_id = b2CreateBody(world_id, &rect_body_def);
    b2Polygon rect = b2MakeBox(1, 0.1);
    b2ShapeDef rect_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(rect_body_id, &rect_shape_def, &rect);

    b2BodyDef bolt1_body_def = b2DefaultBodyDef();
    bolt1_body_def.type = b2_staticBody;
    bolt1_body_def.position = {1,0};
    b2BodyId bolt1_body_id = b2CreateBody(world_id, &bolt1_body_def);
    // b2Polygon bolt1 = b2MakeBox(0.1, 0.1);
    // b2ShapeDef bolt1_shape_def = b2DefaultShapeDef();
    // b2CreatePolygonShape(bolt1_body_id, &bolt1_shape_def, &bolt1);

    b2BodyDef bolt2_body_def = b2DefaultBodyDef();
    bolt2_body_def.type = b2_staticBody;
    bolt2_body_def.position = {-1, 0};
    b2BodyId bolt2_body_id = b2CreateBody(world_id, &bolt2_body_def);
    // b2Polygon bolt2 = b2MakeBox(0.1, 0.1);
    // b2ShapeDef bolt2_shape_def = b2DefaultShapeDef();
    // bolt2_shape_def.isSensor = true;
    // b2CreatePolygonShape(bolt2_body_id, &bolt2_shape_def, &bolt2);


    b2RevoluteJointDef jointDef = b2DefaultRevoluteJointDef();
    jointDef.bodyIdA = rect_body_id;
    jointDef.bodyIdB = bolt1_body_id;
    jointDef.localAnchorA = {1,0};
    jointDef.localAnchorB = {0, 0};
    b2JointId joint1_id = b2CreateRevoluteJoint(world_id, &jointDef);

    b2RevoluteJointDef jointDef2 = b2DefaultRevoluteJointDef();
    jointDef2.bodyIdA = rect_body_id;
    jointDef2.bodyIdB = bolt2_body_id;
    jointDef2.localAnchorA = {-1,0};
    jointDef2.localAnchorB = {0, 0};
    b2JointId joint2_id = b2CreateRevoluteJoint(world_id, &jointDef2);

    RectangleDrawer rect_drawer;

    rect_drawer.texture = TextureLoader::getTexture("resources/wood_texture.jpg");


    bool pressed = false;
    bool pressed2 = false;
    long long int frames = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        frames++;
        auto now_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now_time - prev_time).count() >= 1) {
            std::cout << "FPS: " << frames << std::endl;
            prev_time = std::chrono::steady_clock::now();
            frames = 0;
        }
        b2World_Step(world_id, 1.f/60.f, 4);
        screen.getWindow()->clear();


        b2Vec2 v = b2Body_GetPosition(rect_body_id);
        float rot =  b2Rot_GetAngle(b2Body_GetRotation(rect_body_id));
        rect_drawer.position = {v.x, v.y};
        rect_drawer.rotation = rot;
        rect_drawer.size = {2, 0.2};
        rect_drawer.draw(&screen, &camera);

        // v = b2Body_GetPosition(bolt1_body_id);
        // rot =  b2Rot_GetAngle(b2Body_GetRotation(bolt1_body_id));
        // rect_drawer.position = {v.x, v.y};
        // rect_drawer.rotation = rot;
        // rect_drawer.size = {0.2, 0.2};
        // rect_drawer.draw(&screen, &camera);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !pressed) {
            b2DestroyJoint(joint2_id);
            pressed = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !pressed2) {
            b2DestroyJoint(joint1_id);
            pressed2 = true;
        }


        // state_machine.update();

        // debug_lines(screen.getWindow());

        screen.getWindow()->display();
    }
    screen.destroyWindow();
    TextureLoader::clear();
    SimulationObjectFactory::clear();
    std::cout << "Exiting..." << std::endl;
}
