pybind11_add_module(physics_bindings bindings.cpp)
target_link_libraries(physics_bindings PRIVATE physics_engine)
