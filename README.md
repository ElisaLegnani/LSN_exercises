## LSN exercises

This repository contains the exercises for the Numerical Simulation Laboratory (LSN).


--------------------------------------------------- Folders content ---------------------------------------------------

* 01: pseudo-random number generation and sampling of random variables;
* 02: Monte Carlo integration and simulation of stochastic processes;
* 03: sampling techniques applied to economics;
* 04: Molecular Dynamics simulations;
* 05: Metropolis sampling applied to the hydrogen atom;
* 06: Metropolis and Gibbs sampling applied to the 1D Ising model;
* 07: Metropolis sampling for simulations of Molecular Dynamics;
* 08: Variational Monte Carlo and Path Integral Monte Carlo methods;
* 09: Genetic Algorithm to solve the traveling salesman problem;
* 10: Simulated Annealing algorithm and Parallel Computing to solve the traveling salesman problem;
* 11: Neural Network regression;
* 12: Deep and Convolutional Neural Network image recognition.


------------------------------------------------- Folders organization -------------------------------------------------

In each folder (except for /11 and /12) there is:
* a jupyter notebook, e.g. LSN_Exercises_01.ipynb, where the exercises are explained and results are shown and discussed;
* C++ source codes for the problems solving, e.g. main.cpp, MolDyn_NVE.cpp, TSP.cpp...;
* header files, e.g. main.h, MolDyn_NVE.h, TSP.h...;
* executable files, e.g. main.exe, MolDyn_NVE.exe, TSP.exe...;
* files for random number generation: random.h, random.cpp, Primes, seed.in;
* a Makefile;
* eventually input files with parameters for the code, e.g. input.dat, config.0...;
* output files with results, e.g. *.out;
* eventually a README.md file that explains how to properly run the code;
* evetually a clean.sh file for cleaning contents;

Note: programs and results are eventually contained in folders for different parts of the exercises, e.g. /01.1, /01.2...;

Note: results are eventually stored in folders, e.g. /circle, /square ..., generally named after the type of results they contain.

In folders /11 and /12:
* jupyter notebooks with the exercises explainations and the results, but also the code parts;
