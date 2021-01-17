----------------------------------------- How to run the Monte Carlo ISING 1D code -----------------------------------------

input.dat contains all the parameters needed to run a simulation:
* temperature, number of spins, J, h, number of blocks, number of steps;

it also has the options:
* metro: sampling algorithm (0=Gibbs, 1=Metropolis);
* restart: to continue the simulation from the last configuration config.final of the previous simulation (0=OFF, 1=ON);
* equilibrate: to automatically equilibrate the system (0=OFF, 1=ON);


------------------------------------------- Additional information about the folder  -----------------------------------------

As a task of an exercise is to compute thermodynamic properties at _different_ temperatures, there is an additional jupyter notebook Simulations.ipynb that runs simulations for a range of temperatures (automatically changing the input file) and stores the last results obtained from each in the actual results files for solving the exercise. The complete outputs of the simulations are stored in the folder /results. 
