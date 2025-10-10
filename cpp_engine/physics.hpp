#pragma once
#include <vector>

struct Particle {
    double x, y;
    double vx, vy;
    double mass;
};

class PhysicsEngine {
    public: 
        PhysicsEngine(double dt);
        void addParticle(double x, double y, double vx, double vy, double mass);
        void step();
        std::vector<Particle> getParticles() const;

    private:
        double dt;
        std::vector<Particle> particles;
};