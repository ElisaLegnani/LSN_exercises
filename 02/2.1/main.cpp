/********************************
Numerical Simulation Laboratory
Exercise 02.1
Elisa Legnani
*********************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "random.h"

using namespace std;

double Error(double, double,int);

double f(double);

double c(double);

int main (int argc, char *argv[]){

    //Random number generator
    Random rnd;
    rnd.SetSeed();

    int M=10000; //Number of throws
	int N=100; //Number of blocks
	int L=int(M/N); //Number of throws in each block
    
    double ave=0., ave2=0., err=0.;


    // Part 1: integral computing with uniform sampling
    
    ofstream IntUni("int_uniform.out");
    if(!IntUni.is_open()) cerr << "PROBLEM: Unable to open int_uniform.out" << endl;

    for(int i=0;i<N;i++){
        double integr=0., integr2=0.;
        for(int j=0;j<L;j++){
            double x=rnd.Rannyu();
            integr+=f(x);
        }
        integr/=double(L);
        integr2=integr*integr;
        
        ave=(ave*double(i)+integr)/double(i+1);
        ave2=(ave2*double(i)+integr2)/double(i+1);
        err=Error(ave,ave2,i);
        
        IntUni << (i+1)*L << " " << ave << " " << err << endl;
    }

    IntUni.close();
    

    //Part 2: integral computing with importance sampling

    ofstream IntImp("int_importance.out");
    if(!IntImp.is_open()) cerr << "PROBLEM: Unable to open int_importance.out" << endl;
    
    for(int i=0;i<N;i++){
        double integr=0., integr2=0.;
        for(int j=0;j<L;j++){
            double x=rnd.Rannyu();
            double y=1.-sqrt(1.-x);
            integr+=c(y);
        }
        integr/=double(L);
        integr2=integr*integr;
        
        ave=(ave*double(i)+integr)/double(i+1);
        ave2=(ave2*double(i)+integr2)/double(i+1);
        err=Error(ave,ave2,i);
        
        IntImp << (i+1)*L << " " << ave << " " << err << endl;
    }

    IntImp.close();
    
    rnd.SaveSeed();
    
    return 0;
}


double Error(double ave, double ave2, int n){
    if(n==0) return 0;
    else return sqrt((ave2-ave*ave)/n);
}

double f(double x){
    return M_PI/2.*cos(M_PI*x/2.);
}

double c(double x){
    return M_PI/2.*cos(M_PI*x/2.)/(2.*(1.-x));
}
