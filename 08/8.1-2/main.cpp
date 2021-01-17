/********************************
Numerical Simulation Laboratory
Exercise 08
Elisa Legnani
*********************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "random.h"
#include "main.h"

using namespace std;

int main (int argc, char *argv[]){

    Input();

    for (int i=0; i<neq; i++) Metropolis(); //Equilibration
    if (delta_opt==1) Optimization();

    for(int iblk=0; iblk<nblock; iblk++){
        Reset(iblk);
        for(int l=0; l<L; l++) {
            Metropolis();
            Accumulate();
        }
        Averages(iblk);
    }

    Energy.close();
    Pos.close();

    cout << "Acceptance rate: " << double(accepted)/double(nstep) << endl;
    cout << "Relative error: " << (0.5-double(accepted)/double(nstep))/0.5 << endl << endl;

    rnd.SaveSeed();

    return 0;
}


void Input(void){

    rnd.SetSeed();

    ifstream ReadInput;

    cout << endl << "Ground state of a quantum particle" << endl;
    cout << "in 1D, with external potential V(x)=x^4-5/2*x^2" << endl << endl;
    cout << "Variational Monte Carlo simulation" << endl << endl;
    cout << "The program performs Metropolis moves" << endl << endl;
    cout << "The program uses h-bar=1 and m=1 units" << endl << endl;

    cout << "Transition probability: uniform distribution" << endl;

    ReadInput.open("input.dat");

    ReadInput >> x_0;
    x=x_0;
    cout << "Origin of the simulation: " << x_0 << endl;

    ReadInput >> delta;
    cout << "Time step: " << delta << endl;
    ReadInput >> nstep;
    cout << "Number of steps: " << nstep << endl;
    ReadInput >> nblock;
    cout << "Number of blocks: " << nblock << endl << endl;

    L=nstep/nblock;

    neq=100+x_0*10;

    ReadInput >> mu;
    ReadInput >> sigma;

    ReadInput >> delta_opt;
    if (delta_opt==1) cout << "Automatic time step optimization (on the basis of the acceptance rate)" << endl << endl;
    else cout << "Time step inserted already optimized" << endl << endl;

    ReadInput.close();

    Energy.open("energy.out");
    Pos.open("positions.out");
}

void Optimization(void){
    int n=1000;
    double deltastep=0.1;
    double acc_r1=0;

    for(int j=0; j<1000; j++){
        accepted=0;

        for (int i=0; i<n; i++) Metropolis();

        acc_r1 = double(accepted)/double(n);
        err=(0.5-double(accepted)/double(n))/0.5;

        if (acc_r1<0.5){
            delta-=deltastep;
        } else if (acc_r1>0.5){
            delta+=deltastep;
        }

        if (abs(err)<0.001){
            accepted=0;
            cout << "Optimization interrupted at step " << j << endl;
            break;
        }
    }
    cout << "Optimized time step: " << delta << " (acceptance rate: " << acc_r1 << ", relative error: " << err << ")" << endl << endl;
    accepted=0;
}

void Metropolis(void){
    double y;
    double px, py, A, r;

    //Transition
    y=x+rnd.Rannyu(-delta,delta);

    //Probability to accept
    px=psi2(x);
    py=psi2(y);
    A=min(1.,py/px);

    //Accept?
    r=rnd.Rannyu();
    if (r<=A){
        x=y;
        accepted++;
    }

    Pos << x << endl;
}

void Reset(int iblk){
    blk_ave=0.;
    blk_norm=0;
    if (iblk==0) {ave=0.; ave2=0.; err=0.;}
}

void Accumulate(void){
    H=K(x)+V(x);
    blk_ave+=H;
    blk_norm++;
}

void Averages(int iblk){
    blk_ave=blk_ave/double(blk_norm);
    ave=(ave*double(iblk)+blk_ave)/double(iblk+1);
    ave2=(ave2*double(iblk)+blk_ave*blk_ave)/double(iblk+1);
    err=Error(ave, ave2, iblk);

    Energy << (iblk+1) << " " << ave << " " << err << endl;
}

double psi(double x){
    double n1=-(x-mu)*(x-mu);
    double n2=-(x+mu)*(x+mu);
    double d=2.*sigma*sigma;
    return exp(n1/d)+exp(n2/d);
}

double psi2(double x){
    return pow(psi(x),2);
}

double psi_d2(double x){
    double n1=-(x-mu)*(x-mu);
    double n2=-(x+mu)*(x+mu);
    double d=2.*sigma*sigma;
    double n=(-n1*2/d-1.)*exp(n1/d)+(-n2*2/d-1.)*exp(n2/d);
    return n*2/d;
}

double V(double x){
    return pow(x,4)-5./2.*x*x;
}

double K(double x){
    return -0.5*psi_d2(x)/psi(x);
}

double Error(double ave, double ave2,int iblk){
    if(iblk==0) return 0;
    else return sqrt((ave2-ave*ave)/iblk);
}

