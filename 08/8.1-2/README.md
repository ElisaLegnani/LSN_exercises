---------------------------------------------------- How to run the code ----------------------------------------------------

input.dat contains all the parameters needed to run a simulation:
* starting coordinate x0;
* time step;
* nuber of steps;
* number of blocks;
* parameters of the wave function: mu, sigma;
* delta optimizazion: to automatically optimize the time step in order to have acceptance rate=50% (0=OFF, 1=ON); set it to OFF if the time step inserted is already optimized.

----------------------------------------- Additional information about the folder  ---------------------------------------

As a task of an exercise is to find the parameters mu and sigma that minimize the expectation value of the Hamiltonian, there is an additional jupyter notebook Simulations.ipynb that runs simulations for different parameters (automatically changing the input file) to find it.
