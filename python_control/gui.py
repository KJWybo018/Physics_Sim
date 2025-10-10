import tkinter as tk
from tkinter import filedialog
import json
import physics_bindings

class PhysicsGUI:
  def __init__(self, root):
    self.engine = physics_bindings.PhysicsEngine(0.01)
    self.root = root
    self.root.title("Physics Sim GUI")

    self.entries = {}
    for label in ["x", "y", "vx", "vy", "mass"]:
      tk.label(root, test=label).pack()
      entry = tk.Entry(root)
      entry.pack()
      self.entries[label] = entry

    tk.Button(root, text="Add Particle", command=self.add_particle).pack()
    tk.Button(root, text="Run Step", command=self.run_step).pack()
    tk.Button(root, text="Save", command=self.save_state).pack()
    tk.Button(root, text="Load", command=self.load_state).pack()

    self.canvas = tk.Canvas(root), width=400, height=400, bg="white")
    self.canvas.pack()

  def add_particles(self):
    vals = {k: float(self.entries[k].get()) for k in self.entries}
    self.engine.addParticles(**vals)

  def run_step(self):
    self.engine.step()
    self.draw_particles()

  def draw_particles(self):
    self.canvas.delete("all")
      for p in self.engine.getParticles():
          x, y = p.x * 20 + 200, 400 - p.y * 20
          self.canvas.create_oval(x-5, y-5, x+5, y+5, fill="blue")

  def save_state(self):
      particles = self.engine.getParticles()
      data = [{"x": p.x, "y": p.y, "vx": p.vx, "vy": p.vy, "mass": p.mass} for p in particles]
      file = filedialog.asksaveasfilename(defaultextension=".json")
      if file:
          with open(file, "w") as f:
              json.dump(data, f)

  def load_state(self):
      file = filedialog.askopenfilename(filetypes=[("JSON files", "*.json")])
      if file:
          with open(file, "r") as f:
              data = json.load(f)
          self.engine = physics_bindings.PhysicsEngine(0.01)
          for p in data:
              self.engine.addParticle(**p)
          self.draw_particles()
