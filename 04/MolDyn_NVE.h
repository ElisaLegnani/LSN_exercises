/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

/****************************************************************
Numerical Simulation Laboratory
Exercise 04
Elisa Legnani
*****************************************************************/

using namespace std;

//parameters, observables
const int n_props=5; //number of observables
int iv,ik,ie,it,ip;
double stima_pot, stima_kin, stima_etot, stima_temp, stima_press;

// averages
int blk_norm;
double ave[n_props],ave2[n_props],err[n_props],blk_ave[n_props];

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];
double vx2[m_part],vy2[m_part],vz2[m_part];

//thermodynamical state
int npart;
double energy,temp,vol,rho,box,rcut;

//simulation
int nstep, iprint, nblock, L, seed;
double delta;
bool restart;
string dirname;

//functions
void Input(void);

void InitialConfig(void);
void RestartConfig(void);

void Move(void);

void ConfFinal(void);
void ConfXYZ(int);
void ConfOld(void);

void Measure(void);
double Force(int, int);
double Pbc(double);

void Reset(int);
void Accumulate(void);
void Averages(int);

double Error(double, double,int);

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
