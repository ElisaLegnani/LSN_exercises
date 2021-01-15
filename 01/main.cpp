/********************************
Numerical Simulation Laboratory
Exercise 01.3
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
    
	int M=100000; //Number of throws
	int N=100; //Number of blocks 
	int L=int(M/N); //Number of throws in each block

   double d=1.; //Distance between lines
   double l=0.8; //Needle's length
   int Nhit=0; //Numbers of times the needle intersects a line
    
   double pi=0., pi2=0., ave_pi=0., ave2_pi=0., err_pi=0.;

   ofstream Pi("pi.out");   
   if(!Pi.is_open()) cerr << "PROBLEM: Unable to open pi.out" << endl;
	
	for(int i=0;i<N;i++){
	   Nhit=0.;
      
      //Needle throw
      for(int j=0;j<L;j++){
         double xt, yt, r;

         double xc=rnd.Rannyu(0.,d);
         
         do{
            xt=rnd.Rannyu();
            yt=rnd.Rannyu();
            r=sqrt(xt*xt + yt*yt);
         }while(r>1.);

         //Intersection?
         if ((xc-l/2.*xt/r)<=0. || (xc+l/2.*xt/r)>=d) Nhit++;
      }

		pi=2*l*double(L)/double(Nhit)/d;
		pi2=pi*pi;

      ave_pi=(ave_pi*double(i)+pi)/double(i+1);
      ave2_pi=(ave2_pi*double(i)+pi2)/double(i+1);
      err_pi=Error(ave_pi,ave2_pi,i);
        
      Pi << (i+1)*L << " " << ave_pi << " " << err_pi << endl;
	}

   Pi.close();

   rnd.SaveSeed();
    
   return 0;
}

double Error(double ave, double ave2, int n){
	if(n==0) return 0;
	else return sqrt((ave2-ave*ave)/n);
}