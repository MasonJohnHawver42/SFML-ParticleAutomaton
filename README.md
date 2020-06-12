# ParticleAutomaton
This project was made to capture emergant behavior and to create a ui system for my basic game engine.

# How it Works
This program crestes a system of particles. Each particle has simple rules governing how to interact with other particles. The result of this system is emergent life like behavior. 

# Particles
Each Particle has a type or type. Every type of particle interacts diffrently with difrent particle types. These interactions are generated during the intiation of the world.

# Particle Types
For each particle type contains information about the particle color, its attracttion or repultion from each particle type, and the distances it should interact with other particle types (note: all these atributes are stored in parawell list, but in the futer a either a struct or class should handle these atributes to avoid having parawell lists).
