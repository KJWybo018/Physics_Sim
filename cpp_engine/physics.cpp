#include "physics.hpp"

PhysicsEngine::PhysicsEngine(double dt) : dt(dt) {}

void PhysicsEngine::addParticles(double x, double y, double vx, double vy, double mass) {
    particles.push_back({x, y, vx, vy, mass})
}

void PhysicsEngine::step() {
    for (auto& p : particles) {
        p.vy -= 9.81 * dt;
        p.x += p.vx * dt;
        p.y += p.vy * dt;
    }
}

std::vector<Particle> PhysicsEngine::getParticles() const {
    return particles;
}