/********************************
Numerical Simulation Laboratory
Exercise 05
Elisa Legnani
*********************************/

#include "random.h"

using namespace std;

Random rnd;

//Observables
double x_0, y_0, z_0, radius;
double x[3];

//Simulation
string orbital;
string transition;
double delta;
int nstep, nblock, L, neq, accepted=0;
double (*p)(double, double, double);

//Averages
int blk_norm;
double ave=0.,ave2=0.,err=0.,blk_ave=0.;

//Output
ofstream Radius, Pos;

//Functions
void Input(void);

void Metropolis(void);

void Reset(int);
void Accumulate(void);
void Averages(int);

double psi1s(double, double, double);
double psi2p(double, double, double);

double Error(double, double,int);