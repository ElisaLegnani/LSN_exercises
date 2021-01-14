/****************************************************************
Numerical Simulation Laboratory
Exercise 01.3
Elisa Legnani
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "random.h"

using namespace std;

double Error(double, double,int);  //Function for statistical uncertainty estimation
 
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
    
   double pi=0., pi2=0., m=0., m2=0., err=0.;

   ofstream Pi("pi.out");   
   if(!Pi.is_open()) cerr << "PROBLEM: Unable to open pi.out" << endl;
	
	for(int i=0;i<N;i++){
	   Nhit=0.;
      
      //Needle throw
      for(int j=0;j<L;j++){
         double n=rnd.Rannyu(0.,d);
         double xt, yt, r;
         do{
            xt=rnd.Rannyu();
            yt=rnd.Rannyu();
            r=sqrt(xt*xt + yt*yt);
         }while(r>1.);

         //Intersection?
         if ((n-l/2.*xt/r)<=0. || (n+l/2.*xt/r)>=d) Nhit++;
      }

		pi=2*l*double(L)/double(Nhit)/d;
		pi2=pi*pi;

      m=(m*double(i)+pi)/double(i+1);
      m2=(m2*double(i)+pi2)/double(i+1);
      err=Error(m,m2,i);
        
      Pi << (i+1)*L << " " << m << " " << err << endl;
	}

   Pi.close();

   rnd.SaveSeed();
    
   return 0;
}

double Error(double ave, double ave2, int n){
	if(n==0) return 0;
	else return sqrt((ave2-ave*ave)/n);
}
