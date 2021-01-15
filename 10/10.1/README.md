------------------------------------- How to run the Traveling Salesman Problem (Simulated Annealing) code -------------------------------------

input.dat contains all the parameters needed to run the code:
* number of cities, configuration of cities (circle or square),
* initial temperature, temperature decay rate, number of temperature steps,
* number of Metropolis steps; 

Note: the program generates random numbers reading the file seed.out that a previous run has produced,
so that at every run it generates a different random configuration of cities.

Note: number of Metropolis steps must be at least 100 times the number of temperature steps.
