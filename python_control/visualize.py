import matplotlib.pyplot as plt

def plot_particles(particles):
    xs = [p.x for p in particles]
    ys = [p.y for p in particles]
    plt.clf()
    plt.scatter(xs, ys)
    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.pause(0.01)
