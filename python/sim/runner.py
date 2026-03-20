from __future__ import annotations
from typing import Callable, Optional
import time
 
try:
    from physics_engine import World, Vec3, EulerIntegrator  # compiled C++ module
    _HAS_ENGINE = True
except ImportError:
    _HAS_ENGINE = False
    print("[SimRunner] WARNING: physics_engine module not found. "
          "Build the C++ extension first (see CMakeLists.txt).")
 
 
StepHook = Callable[["SimRunner", float], None]
 
 
class SimRunner:
    """
    High-level simulation runner.
 
    Usage::
 
        runner = SimRunner(gravity=-9.81, dt=1/60)
        runner.world.add_body("box", mass=1.0, pos=Vec3(0, 10, 0))
        runner.add_hook(my_logger.on_step)
        runner.run(duration=5.0)
    """
 
    def __init__(
        self,
        gravity: float = -9.81,
        dt: float = 1.0 / 60.0,
        integrator: str = "euler",
    ):
        if not _HAS_ENGINE:
            raise RuntimeError("C++ physics_engine module is not available.")
 
        self.dt = dt
        self._hooks: list[StepHook] = []
 
        self.world = World(gravity)
        self.world.set_integrator(integrator)
 
 
    def add_hook(self, fn: StepHook) -> None:
        """Register a callable invoked after every physics step."""
        self._hooks.append(fn)
 
    def remove_hook(self, fn: StepHook) -> None:
        self._hooks.remove(fn)
 
 
    def step(self) -> None:
        """Advance the simulation by one timestep and call all hooks."""
        self.world.step(self.dt)
        for hook in self._hooks:
            hook(self, self.world.time)
 
    def run(
        self,
        duration: float,
        realtime: bool = False,
        on_collision: Optional[Callable] = None,
    ) -> None:
        """
        Run for `duration` seconds of simulation time.
 
        Args:
            duration:     Simulated seconds to run.
            realtime:     If True, sleep between steps to match wall time.
            on_collision: Optional callback(event) called per collision.
        """
        n_steps = int(duration / self.dt)
        wall_start = time.perf_counter()
 
        for i in range(n_steps):
            self.step()
 
            if on_collision:
                for event in self.world.collision_events:
                    on_collision(event)
 
            if realtime:
                target = wall_start + (i + 1) * self.dt
                sleep_s = target - time.perf_counter()
                if sleep_s > 0:
                    time.sleep(sleep_s)
 
    # --- Convenience helpers ---
 
    def add_body(self, name: str, mass: float = 1.0,
                 pos: tuple = (0, 0, 0), vel: tuple = (0, 0, 0)):
        """Add a rigid body using plain tuples for position/velocity."""
        return self.world.add_body(
            name, mass,
            Vec3(*pos),
            Vec3(*vel),
        )
 
    def get_body(self, name: str):
        return self.world.get_body(name)
 
    def apply_force(self, body_name: str, force: tuple) -> None:
        body = self.get_body(body_name)
        if body is None:
            raise KeyError(f"Body '{body_name}' not found in world.")
        body.apply_force(Vec3(*force))
 
    def snapshot(self) -> dict:
        """Return a serialisable snapshot of the current world state."""
        return {
            "time": self.world.time,
            "bodies": [
                {
                    "name":     b.name,
                    "position": (b.position.x, b.position.y, b.position.z),
                    "velocity": (b.velocity.x, b.velocity.y, b.velocity.z),
                    "mass":     b.mass,
                }
                for b in self.world.bodies
            ],
        }
 
    def __repr__(self):
        return (f"<SimRunner t={self.world.time:.3f}s "
                f"dt={self.dt} bodies={len(list(self.world.bodies))}>") 
