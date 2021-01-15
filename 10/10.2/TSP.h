/********************************
Numerical Simulation Laboratory
Exercise 10.2
Elisa Legnani
*********************************/

#ifndef __TSP__
#define __TSP__

#include <vector>
#include "random.h"

using namespace std;

Random rnd;

//Parallel computing
int Size, Rank;
void Migration(void);

//Population
int ncities, npaths;
string config;
const int n_coord = 2;
vector<vector<double>> population, coordinates;

//Simulation of generations
int ngens;
double pc, pm;

void Input(void);
void NewPopulation(void); //Of random paths
vector<double> RandomPath(int);
void Sort(void); //Calculate paths' lengths and sort paths (on min length basis)

void NewGeneration(double,double); //After crossover and mutations
vector<vector<double>> Crossover(int,int);
int Selection(void);

double Distance(vector<double>, vector<double>); //Between cities
double Length(vector<double>); //Of a path
bool ComparePaths(vector<double> v1, vector<double> v2);

//Cities configurations
void Circumference(void);
void Square(void);

//Print functions
void PrintCities(void);
void PrintBestPath(void);
void PrintBestLength(int);

#endif
