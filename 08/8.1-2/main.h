/********************************
Numerical Simulation Laboratory
Exercise 08
Elisa Legnani
*********************************/

using namespace std;

#include "random.h"
Random rnd;

//Observables
double x_0, x;
double H;
double mu, sigma;

//Simulation
double delta;
int nstep, nblock, L, neq, accepted=0, delta_opt;

//Averages
int blk_norm;
double ave=0.,ave2=0.,err=0.,blk_ave=0.;

//Output
ofstream Energy, Pos;

//Functions
void Input(void);
void Optimization(void);

void Metropolis(void);

void Reset(int);
void Accumulate(void);
void Averages(int);

double psi(double);
double psi2(double);
double psi_d2(double);
double V(double);
double K(double);

double Error(double, double,int);