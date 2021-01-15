----------------------------- How to run the Traveling Salesman Problem (Parallel Genetic Algorithm) code -----------------------------

input.dat contains all the parameters needed to run the code:
* number of cities, configuration of cities (circle or square),
* number of paths, number of generations,
* crossover probability, mutation probability; 

Note: the program generates random numbers reading the file seed.out that a previous run has produced,
so that at every run it generates a different random configuration of cities.

Note: the code has N_migr set to 20; to change it, one has to modify TSP.cpp.
