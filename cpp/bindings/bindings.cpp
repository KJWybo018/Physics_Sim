#include <pybind11/pybind11.h>
#include <pybind11/st1.h>

#include "World.h"
#include "RigidBody.h"
#include "Integrator.h"
#include "Vec3.h"

namespace py = pybind11;

PYBIND11_MODULE(physics_engine, m) {
    m.doc() = "C++ physics engine — Python bindings via pybind11";
 
    // --- Vec3 ---
    py::class_<Vec3>(m, "Vec3")
        .def(py::init<>())
        .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
        .def_readwrite("x", &Vec3::x)
        .def_readwrite("y", &Vec3::y)
        .def_readwrite("z", &Vec3::z)
        .def("norm",       &Vec3::norm)
        .def("normalized", &Vec3::normalized)
        .def("dot",        &Vec3::dot)
        .def("cross",      &Vec3::cross)
        .def("__add__",    &Vec3::operator+)
        .def("__sub__",    &Vec3::operator-)
        .def("__mul__",    [](const Vec3& v, double s){ return v * s; })
        .def("__repr__",   &Vec3::str);
 
    // --- RigidBody ---
    py::class_<RigidBody>(m, "RigidBody")
        .def_readonly("name",             &RigidBody::name)
        .def_readwrite("position",        &RigidBody::position)
        .def_readwrite("velocity",        &RigidBody::velocity)
        .def_readwrite("acceleration",    &RigidBody::acceleration)
        .def_readwrite("angular_velocity",&RigidBody::angular_velocity)
        .def_readwrite("mass",            &RigidBody::mass)
        .def_readwrite("restitution",     &RigidBody::restitution)
        .def_readwrite("linear_damping",  &RigidBody::linear_damping)
        .def_readwrite("angular_damping", &RigidBody::angular_damping)
        .def("apply_force",    &RigidBody::apply_force)
        .def("apply_force_at", &RigidBody::apply_force_at)
        .def("is_static",      &RigidBody::is_static)
        .def("__repr__", [](const RigidBody& b){
            return "<RigidBody '" + b.name + "' pos=" + b.position.str() + ">";
        });
 
    // --- CollisionEvent ---
    py::class_<CollisionEvent>(m, "CollisionEvent")
        .def_readonly("body_a",         &CollisionEvent::body_a)
        .def_readonly("body_b",         &CollisionEvent::body_b)
        .def_readonly("contact_point",  &CollisionEvent::contact_point)
        .def_readonly("contact_normal", &CollisionEvent::contact_normal)
        .def_readonly("impulse",        &CollisionEvent::impulse);
 
    // --- Integrators ---
    py::class_<Integrator>(m, "Integrator")
        .def("name", &Integrator::name);
 
    py::class_<EulerIntegrator, Integrator>(m, "EulerIntegrator")
        .def(py::init<>());
 
    py::class_<VerletIntegrator, Integrator>(m, "VerletIntegrator")
        .def(py::init<>());
 
    py::class_<RK4Integrator, Integrator>(m, "RK4Integrator")
        .def(py::init<>());
 
    // --- World ---
    py::class_<World>(m, "World")
        .def(py::init<double>(), py::arg("gravity") = -9.81)
        .def("add_body", &World::add_body,
             py::arg("name"), py::arg("mass") = 1.0,
             py::arg("pos")  = Vec3{},
             py::arg("vel")  = Vec3{},
             py::return_value_policy::reference)
        .def("get_body", &World::get_body,
             py::arg("name"),
             py::return_value_policy::reference)
        .def("remove_body",      &World::remove_body)
        .def("set_integrator",   [](World& w, const std::string& name){
            if      (name == "euler")  w.set_integrator(std::make_unique<EulerIntegrator>());
            else if (name == "verlet") w.set_integrator(std::make_unique<VerletIntegrator>());
            else if (name == "rk4")    w.set_integrator(std::make_unique<RK4Integrator>());
            else throw std::invalid_argument("Unknown integrator: " + name);
        }, py::arg("name"))
        .def("step",             &World::step, py::arg("dt"))
        .def("reset",            &World::reset)
        .def_property_readonly("time",            &World::time)
        .def_property("gravity", &World::gravity, &World::set_gravity)
        .def_property_readonly("collision_events",&World::collision_events);
}
