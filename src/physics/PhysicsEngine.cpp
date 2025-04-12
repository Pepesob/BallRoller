#include "PhysicsEngine.hpp"

#include <thread>

#include <Box2D/box2d.h>
#include <iostream>

PhysicsEngine::PhysicsEngine(float gravity_x, float gravity_y) {
	this->gravity = {gravity_x, gravity_y};

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = this->gravity;

	this->worldId = b2CreateWorld( &worldDef );
	this->started = false;
}

PhysicsEngine::~PhysicsEngine() {
	b2DestroyWorld(this->worldId);
}

// void PhysicsEngine::subscribe(CollisionObserver *observer) {
// 	this->collision_observers.push_back(observer);
// }
//
// void PhysicsEngine::unsubscribe(CollisionObserver *observer) {
// 	std::vector<CollisionObserver*>::iterator newEnd = std::ranges::remove(collision_observers, observer).begin();
// 	this->collision_observers.erase(newEnd);
// }

void PhysicsEngine::start() {
	this->prev_time = prev_time = std::chrono::steady_clock::now();
	this->started = true;
}

void PhysicsEngine::stop() {
	this->started = false;
}

void PhysicsEngine::update() {
	if (!this->started) {
		throw std::runtime_error("PhysicsEngine is not started");
	}
	std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->prev_time);
	int possible_step_count = static_cast<float>(diff.count()) / (this->timeStep * 1000.);

	int actual_step_count = std::ceil(std::sqrt(possible_step_count));
	// std::cout << "----------------------------" << std::endl;
	// std::cout << possible_step_count << " possible steps" << std::endl;
	// std::cout << actual_step_count << " steps" << std::endl;
	// std::cout << "----------------------------" << std::endl;
	for (int i = 0; i < actual_step_count; i++) {
		b2World_Step(worldId, timeStep, subStepCount);
	}
	// this->collisionNotify();
	std::chrono::milliseconds delta_ms(static_cast<long long>(actual_step_count * this->timeStep * 1000.0));
	this->prev_time += delta_ms;
}

b2WorldId PhysicsEngine::getWorldId() const {
	return worldId;
}

// void PhysicsEngine::collisionNotify() {
// 	b2ContactEvents contactEvents = b2World_GetContactEvents(this->getWorldId());
// 	for (int i = 0; i < contactEvents.beginCount; ++i)
// 	{
// 		b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
// 		// std::cout << "++++++++++++++++++++++++++" << std::endl;
// 		// std::cout << beginEvent->shapeIdA.index1 << std::endl;
// 		// std::cout << beginEvent->shapeIdB.index1 << std::endl;
// 		for (const auto obs: this->collision_observers) {
// 			obs->update(beginEvent->shapeIdA, beginEvent->shapeIdB);
// 		}
// 	}
// }
