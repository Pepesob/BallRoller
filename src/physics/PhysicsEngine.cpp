#include "PhysicsEngine.hpp"

#include <thread>

#include <Box2D/box2d.h>


PhysicsEngine::PhysicsEngine(Vector2D gravity) {
	this->gravity = gravity;

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = {this->gravity.x, this->gravity.y};

	this->world_id = b2CreateWorld( &worldDef );
	this->collision_manager = new CollisionManager(this->world_id);
	this->started = false;
}

PhysicsEngine::~PhysicsEngine() {
	b2DestroyWorld(this->world_id);
}

void PhysicsEngine::start() {
	this->prev_time = prev_time = std::chrono::steady_clock::now();
	this->collision_manager->setObjectPhysicsList(&this->objects);
	this->started = true;
}

void PhysicsEngine::stop() {
	this->started = false;
}

void PhysicsEngine::step() {
	if (!this->started) {
		throw std::runtime_error("PhysicsEngine is not started");
	}
	std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->prev_time);
	int possible_step_count = static_cast<float>(diff.count()) / (this->timeStep * 1000.);

	int actual_step_count = std::ceil(std::sqrt(possible_step_count)) > 0 ? 1 : 0;

	for (int i = 0; i < actual_step_count; i++) {
		b2World_Step(world_id, timeStep, subStepCount);
		this->collision_manager->collisionNotify();
		this->callStepOnObjects();
	}

	std::chrono::milliseconds delta_ms(static_cast<long long>(actual_step_count * this->timeStep * 1000.0));
	this->prev_time += delta_ms;
}

b2WorldId PhysicsEngine::getWorldId() const {
	return world_id;
}

