#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cpp_engine/physics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(physics_bindings, m) {
    py::class_<Particle>(m, "Particle")
        .def_readonly("x", &Particle::x)
        .def_readonly("y", &Particle::y)
        .def_readonly("vx", &Particle::vx)
        .def_readonly("vy", &Particle::vy)
        .def_readonly("mass", &Particle::mass);

    py::class_<PhysicsEngine>(m, "PhysicsEngine")
        .def(py::init<double>())
        .def("addParticle", &PhysicsEngine::addParticle)
        .def("step", &PhysicsEngine::step)
        .def("getParticles", &PhysicsEngine::getParticles);
}
