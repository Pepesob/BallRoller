#include "PhysicsEngine.hpp"

#include <thread>

#include <Box2D/box2d.h>
#include <iostream>

PhysicsEngine::PhysicsEngine(float gravity_x, float gravity_y) {
	this->gravity = {gravity_x, gravity_y};

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = this->gravity;

	this->world_id = b2CreateWorld( &worldDef );
	this->started = false;
}

PhysicsEngine::~PhysicsEngine() {
	b2DestroyWorld(this->world_id);
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

	int actual_step_count = std::ceil(std::sqrt(possible_step_count)) > 0 ? 1 : 0;

	for (int i = 0; i < actual_step_count; i++) {
		b2World_Step(world_id, timeStep, subStepCount);
	}
	// this->collisionNotify();
	std::chrono::milliseconds delta_ms(static_cast<long long>(actual_step_count * this->timeStep * 1000.0));
	this->prev_time += delta_ms;
}

b2WorldId PhysicsEngine::getWorldId() const {
	return world_id;
}

