import physics_bindings

def setup_sim():
    engine = physics_bindings.PhysicsEngine(0.01)
    engine.addParticle(x=0, y=0, vx=1, vy=5, mass=1)
    engine.addParticle(x=1, y=2, vx=-1, vy=3, mass=2)
    return engine
