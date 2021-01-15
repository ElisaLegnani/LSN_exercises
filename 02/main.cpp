/********************************
Numerical Simulation Laboratory
Exercise 02.2
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

double Distance(double[]); //3D distance

int main (int argc, char *argv[]){

    //Random number generator
    Random rnd;
    rnd.SetSeed();

    int M=10000; //Number of throws
	int N=100; //Number of blocks
	int L=int(M/N); //Number of throws in each block
    
    int S=100; //Number of steps
    double a=1.; //Step's lenght
    double pos[3]; //Previous position
    
    double rms[N][S]; //Mean on every block for every step
    double ave=0., ave2=0., err=0.;
    

    // Part 1: discrete 3D RW
    
    ofstream DiscrRW("rw_discrete.out");
    if(!DiscrRW.is_open()) cerr << "PROBLEM: Unable to open rw_discrete.out" << endl;

    for(int i=0;i<N;i++){
        for(int s=0; s<S; s++) rms[i][s]=0.;
    }

    for(int i=0;i<N;i++){

        for(int j=0;j<L;j++){
            for (int dim=0; dim<3; dim++) pos[dim]=0;

            for(int s=0;s<S;s++){
                int dir=rnd.Rannyu(0.,3.); //Direction
                int fb=rnd.Rannyu(0.,2.); //Forward or backward
            
                if (fb==0) pos[dir]+=a;
                else pos[dir]-=a;

                double r=Distance(pos); //Distance from origin after a step
                rms[i][s]+=r*r; 
                if (j==(L-1)) rms[i][s]/=double(L);
            }
        }    
    }

    for(int s=0;s<S;s++){
        ave=0; ave2=0.; err=0.;
        
        for(int i=0;i<N;i++){
            ave+=rms[i][s];
            ave2+=rms[i][s]*rms[i][s];
        }
        
        ave/=double(N);
        ave2/=double(N);
        err=Error(ave,ave2,N);

        ave=pow(ave,0.5);

        DiscrRW << (s+1) << " " << ave << " " << err << endl;
    }

    DiscrRW.close();
    

    //Part 2: continuous 3D RW
    
    ofstream ContRW("rw_continuous.out");
    if(!ContRW.is_open()) cerr << "PROBLEM: Unable to open rw_continuous.out" << endl;
    
    for(int i=0;i<N;i++){
        for(int s=0; s<S; s++) rms[i][s]=0.;
    }

    for(int i=0;i<N;i++){

        for(int j=0;j<L;j++){
            for (int dim=0; dim<3; dim++) pos[dim]=0;

            for(int s=0;s<S;s++){
                double x=rnd.Rannyu();
                double theta=acos(1.-2*x);
                double phi=rnd.Rannyu()*2*M_PI;

                pos[0]+=a*sin(theta)*cos(phi);
                pos[1]+=a*sin(theta)*sin(phi);
                pos[2]+=a*cos(theta);
                
                double r=Distance(pos);
                rms[i][s]+=r*r; 
                if (j==(L-1)) rms[i][s]/=double(L);
            }
        }    
    }

    for(int s=0;s<S;s++){
        ave=0; ave2=0.; err=0.;
        
        for(int i=0;i<N;i++){
            ave+=rms[i][s];
            ave2+=rms[i][s]*rms[i][s];
        }
        
        ave/=double(N);
        ave2/=double(N);
        err=Error(ave,ave2,N);

        ave=pow(ave,0.5);

        ContRW << (s+1) << " " << ave << " " << err << endl;
    }

    ContRW.close();
    
    rnd.SaveSeed();
    
    return 0;
}


double Error(double ave, double ave2, int n){
    if(n==0) return 0;
    else return sqrt((ave2-ave*ave)/n);
}

double Distance(double pos[]){
    return sqrt(pos[0]*pos[0]+pos[1]*pos[1]+pos[2]*pos[2]);
}