// Author: Kyle W
// File Name: include/World.h

#pragma once
#include "RigidBody.h"
#include "Integrator.h"
#include <vector>
#include <memory>
#include <string>

struct CollisionEvent {
  std::string body_a;
  std::string body_b;
  Vec3 contact_point;
  Vec3 contact_normal;
  double impulse;
};

class World {
public:
  explicit World(double gravity = -9.81);

  RigidBody* add_body(const std::string& name, double mass = 1.0, Vec3 pos = {}, Vec3 vel = {});
  RigidBody* get_body(const std::string& name);
  void remove_body(const std::string& name);
  const std::vector<std::unique_ptr<RigidBody>>& bodies() const { return bodies; };

  void set_integrator(std::unique_ptr<Integrator> integrator);

  void step(double dt);
  void reset();

  double time() const { return time_; };
  double gravity() const { return gravity_; };
  void set_gravity(double g) { gravity_ = g; };

  const std::vector<CollisionEvent>& collision_events() const { return collision_events_; };

private:
  double gravity_;
  double time_ = 0.0;

  std::vector<std::unique_ptr<RigidBody>> bodies_;
  std::unique_ptr<Integrator> integrator_;
  std::vector<CollisionEvent> collsion_events_;

  void apply_gravity_();
  void detect_ground_collsions_();
};
