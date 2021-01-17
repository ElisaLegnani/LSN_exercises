/********************************
Numerical Simulation Laboratory
Exercise 05
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
    
    for(int iblk=0; iblk<nblock; iblk++){
        Reset(iblk);
        for(int l=0; l<L; l++) {
            Metropolis();
            Accumulate();
        }
        Averages(iblk);
    }
  
    Radius.close();
    Pos.close();

    cout << "Acceptance rate: " << double(accepted)/double(nstep) << endl;
    cout << "Relative error: " << (0.5-double(accepted)/double(nstep))/0.5 << endl << endl;
  
    rnd.SaveSeed();
        
    return 0;
}


void Input(void){
  
    rnd.SetSeed();

    ifstream ReadInput;

    cout << endl << "Hydrogen atom" << endl;
    cout << "Monte Carlo simulation" << endl << endl;
    cout << "The program performs Metropolis moves" << endl;
    cout << "to sample the square of the absolute value of the Hydrogen wave function" << endl << endl;
    cout << "The program uses Bohr radius units " << endl << endl;
  
    ReadInput.open("input.dat");

    ReadInput >> orbital;
    cout << "Orbital: " << orbital << endl;
    if (orbital=="1s") p=&psi1s;
    else if(orbital=="2p") p=&psi2p;
    else{
        cerr << "PROBLEM: insert the orbital for simulation: '1s' or '2p'." << endl << endl;
        exit(1);
    }
  
    ReadInput >> x_0;
    x[0]=x_0;
    ReadInput >> y_0; 
    x[1]=y_0;
    ReadInput >> z_0;
    x[2]=z_0;
    cout << "Origin of the simulation: ("<<x_0<<", "<<y_0<<", "<<z_0<<")" << endl;
  
    ReadInput >> delta;
    cout << "Time step: " << delta << endl;
    
    ReadInput >> transition;
    if (transition=="uniform") cout << "Transition probability: uniform distribution" << endl;
    else if(transition=="gaussian") cout << "Transition probability: gaussian distribution" << endl;
    else{
        cerr << "PROBLEM: insert the transition probability: 'uniform' or 'gaussian'" << endl << endl;
        exit(1);
    }
    
    ReadInput >> nstep;
    cout << "Number of steps: " << nstep << endl;
    ReadInput >> nblock;
    cout << "Number of blocks: " << nblock << endl << endl;

    L=nstep/nblock;

    int max_coord=max({x_0,y_0,z_0}); 
    neq=max_coord*10;
  
    ReadInput.close();
  
    Radius.open(transition+"/"+orbital+"_radius.out");
    Pos.open(transition+"/"+orbital+"_positions.out");
}

void Metropolis(void){
    double y[3];
    double px, py, A, r;
  
    //Transition
    if(transition=="uniform"){
        for (int i=0; i<3; i++) y[i]=x[i]+rnd.Rannyu(-delta,delta);
    }else if(transition=="gaussian"){
        for (int i=0; i<3; i++) y[i]=rnd.Gauss(x[i],delta);
    }
  
    //Probability to accept
    px=p(x[0],x[1],x[2]);
    py=p(y[0],y[1],y[2]);
    A=min(1.,py/px);
  
    //Accept?
    r=rnd.Rannyu();
    if (r<=A){
        for(int i=0; i<3; i++) x[i]=y[i];
        accepted++;
    }
  
    Pos << x[0] << " " << x[1] << " " << x[2] << endl;
}

void Reset(int iblk){
    blk_ave=0.;
    blk_norm=0;
    if (iblk==0) {ave=0.; ave2=0.; err=0.;}
}

void Accumulate(void){ 
    radius=sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    blk_ave+=radius;
    blk_norm++;
}

void Averages(int iblk){
    blk_ave=blk_ave/double(blk_norm);
    ave=(ave*double(iblk)+blk_ave)/double(iblk+1);
    ave2=(ave2*double(iblk)+blk_ave*blk_ave)/double(iblk+1);
    err=Error(ave, ave2, iblk);
    
    Radius << (iblk+1) << " " << ave << " " << err << endl;
}

double psi1s(double x, double y, double z){ //Square of the absolute value of psi
    double r=sqrt(x*x+y*y+z*z);
    return exp(-2.*r)/M_PI;
}

double psi2p(double x, double y, double z){ //Square of the absolute value of psi
    double r=sqrt(x*x+y*y+z*z);
    double cos_theta=z/r;
    return r*r*exp(-r)*cos_theta*cos_theta/32./M_PI;
}

double Error(double ave, double ave2,int iblk){
    if(iblk==0) return 0;
    else return sqrt((ave2-ave*ave)/iblk);
}
