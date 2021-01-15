/********************************
Numerical Simulation Laboratory
Exercise 03
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

int main (int argc, char *argv[]){

    //Random number generator
    Random rnd;
    rnd.SetSeed();

    int M=100000;
    int N=100;
    int L=int(M/N);

    double S0=100.;//Asset price at t=0
    double T=1.; //Delivery time
    double K=100.; //Strike price
    double r=0.1; //Risk-free interest rate
    double sigma=0.25; //Volatility

    double ave_call=0., ave_call2=0., err_call=0.;
    double ave_put=0.,  ave_put2=0., err_put=0.;

    // Part 1: direct sampling
    
    ofstream DirectCall("direct_call.out");
        if(!DirectCall.is_open()) cerr << "PROBLEM: Unable to open direct_call.out" << endl;
    ofstream DirectPut("direct_put.out");
        if(!DirectPut.is_open()) cerr << "PROBLEM: Unable to open direct_put.out" << endl;
    
    for(int i=0;i<N;i++){
        double call=0., put=0.;
        for(int j=0;j<L;j++){
            double WT=rnd.Gauss(0.,T);
            double ST=S0*exp((r-0.5*sigma*sigma)*T+sigma*WT);
            call+=max(0.,ST-K)*exp(-r*T);
            put+=max(0.,K-ST)*exp(-r*T);
        }
        call/=double(L);
        put/=double(L);
        
        ave_call=(ave_call*double(i)+call)/double(i+1);
        ave_call2=(ave_call2*double(i)+call*call)/double(i+1);
        err_call=Error(ave_call,ave_call2,i);

        ave_put=(ave_put*double(i)+put)/double(i+1);
        ave_put2=(ave_put2*double(i)+put*put)/double(i+1);
        err_put=Error(ave_put,ave_put2,i);
        
        DirectCall << (i+1)*L << " " << ave_call << " " << err_call << endl;
        DirectPut << (i+1)*L << " " << ave_put << " " << err_put << endl;
    }

    DirectCall.close();
    DirectPut.close();
    
    //Part 2: discretized sampling

    int nsteps=100;
    double dT=T/double(nsteps);
    
    ofstream DiscreteCall("discrete_call.out");
        if(!DiscreteCall.is_open()) cerr << "PROBLEM: Unable to open discrete_call.out" << endl;
    ofstream DiscretePut("discrete_put.out");
        if(!DiscretePut.is_open()) cerr << "PROBLEM: Unable to open discrete_put.out" << endl;
    
    for(int i=0;i<N;i++){
        double call=0., put=0.;
        for(int j=0;j<L;j++){
            double ST=S0;
            for(int s=0; s<nsteps; s++){
                double Z=rnd.Gauss(0.,1.);
                ST=ST*exp((r-0.5*sigma*sigma)*dT+sigma*Z*sqrt(dT));
            }
            call+=max(0.,ST-K)*exp(-r*T);
            put+=max(0.,K-ST)*exp(-r*T);
        }
        call/=double(L);
        put/=double(L);
        
        ave_call=(ave_call*double(i)+call)/double(i+1);
        ave_call2=(ave_call2*double(i)+call*call)/double(i+1);
        err_call=Error(ave_call,ave_call2,i);
        
        ave_put=(ave_put*double(i)+put)/double(i+1);
        ave_put2=(ave_put2*double(i)+put*put)/double(i+1);
        err_put=Error(ave_put,ave_put2,i);
        
        DiscreteCall << (i+1)*L << " " << ave_call << " " << err_call << endl;
        DiscretePut << (i+1)*L << " " << ave_put << " " << err_put << endl;
    }

    DiscreteCall.close();
    DiscretePut.close();

    rnd.SaveSeed();
    
    return 0;
}


double Error(double ave, double ave2, int n){
    if(n==0) return 0;
    else return sqrt((ave2-ave*ave)/n);
}
