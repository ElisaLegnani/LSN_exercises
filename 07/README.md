-------------------------------------------- How to run the Monte Carlo NVT code --------------------------------------------

input.dat contains all the parameters needed to run a simulation:
* temperature, number of particles, particle density, cut-off radius
* time step, number of blocks, number of steps; 

input.solid, input.liquid and input.gas contain the thermodynamic parameters (in LJ units) for the input.dat file that are characteristic of each phase and the optimized parameters for the simulation.

Note: in the code there is the option to print the configuration in .xyz format every 10 steps, that is commented to avoid "filesystem full"; to use it, uncomment it and re-compile the program.

Note: also the function to print istant values of the observables is disabled, as it is a computationally expensive task; it was used to set the simulation parameters and then it was commented.

------------------------------------------- Additional information about the folder  -----------------------------------------

The folder /NVE contains the implemented MD code for simulations of Argon in SI units. For informations about running it and equilibrating the system see execise 4.
