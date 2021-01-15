------------------------------------------ How to run the Molecular Dynamics code ----------------------------------------

input.dat contains all the parameters needed to run a simulation:
* temperature, number of particles, particle density, cut-off radius, time step, number of steps; 

it also has the options:
* restart: to continue the simulation from the last two configurations old.0 and old.final of the previous simulation and rescale velocities (0=OFF, 1=ON);
* nblock: to compute mean values and uncertainties for each block with the blocking method;
* dirname: the directory where the results are printed. 

input.equi, input.solid, input.liquid and input.gas contain the parameters (in LJ units) for the input.dat file that are characteristic of each phase.

Note: in the code there is the option to print the configuration in .xyz format every 10 steps, that is commented to avoid "filesystem full"; to use it, uncomment it and re-compile the program.

----------------------------------------- Additional information about the folder  ---------------------------------------


The MD code for simulations of Argon in SI units is implemented in the /Argon folder.


---------------------------------------------- How to equilibrate the system ----------------------------------------------


1. Run 'make clean.sim' : delete previous configurations and output data;

2. in input.dat set restart to 0 (start from initial fcc configuration config.0 and extract random velocities);

3. in input.dat set nstep to 1000 to accelerate the process of equilibration;

4. run './MolDyn_NVE.exe';

5. change restart to 1 (start from previous configurations and rescale velocities);

6. run './MolDyn_NVE.exe' for at least 5 times;

7. run 'bash clean.sh': delete output data;

8. change number of steps to 10000 or more for the real simulation.

--> The system is equilibrated and ready for the real simulation.
