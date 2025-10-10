from python_control.controller import setup_sim
from python_control.visualize import plot_particles

engine = setup_sim()

import matplotlib.pyplot as plt
plt.ion()

for _ in range(500):
    engine.step()
    plot_particles(engine.getParticles())

plt.savefig("snapshot.png")

