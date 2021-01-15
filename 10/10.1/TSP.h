/********************************
Numerical Simulation Laboratory
Exercise 10.1
Elisa Legnani
*********************************/

#ifndef __TSP__
#define __TSP__

#include <vector>
#include "random.h"

using namespace std;

Random rnd;

//Path
int ncities;
string config;
const int n_coord = 2;
vector<vector<double>> coordinates;
vector<double> path, bestpath;
double bestlength;

//Simulation
int tstep=0, tsteps, nsteps;
double temp, trate;
int attempted, accepted;
double beta;
double alpha, e;

void Input(void);
vector<double> RandomPath(int);

void Reset(void);
vector<double> Mutation(vector<double>);
void Metropolis(void);
void FindBestLength(void);

double Distance(vector<double>, vector<double>); //Between cities
double Length(vector<double>); //Of a path

//Cities configurations
void Circumference(void);
void Square(void);

//Print functions
void PrintCities(void);
void PrintBestPath(void);
void PrintBestLength(int);

#endif
