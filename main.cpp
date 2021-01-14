/****************************************************************
Numerical Simulation Laboratory
Exercise 01.1
Elisa Legnani
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "random.h"

using namespace std;

//Function for statistical uncertainty estimation
double Error(double, double, int);
 
int main (int argc, char *argv[]){

   //Random number generator
   Random rnd;
	rnd.SetSeed();

   //Part 1: estimation of ⟨𝑟⟩ and its uncertainty
    
	int M=10000; //Number of throws
	int N=100; //Number of blocks
	int L=int(M/N); //Number of throws in each block

	double m[N]; //r_i
	double m2[N]; //(r_i)^2
    
   double n, s, s2, err;

   ofstream Mean("mean.out");   
   if(!Mean.is_open()) cerr << "PROBLEM: Unable to open mean.out" << endl;
	
	for(int i=0;i<N;i++){
	   s=0.;
      for(int j=0;j<L;j++){
         n=rnd.Rannyu();
         s+=n;
      }
		m[i]=s/double(L); 
		m2[i]=m[i]*m[i];
	}

	for(int i=0;i<N;i++){
      s=0.; s2=0.; err=0.;
		for(int j=0;j<(i+1);j++){
			s+=m[j];
			s2+=m2[j];
		}
		s/=double(i+1); //Cumulative average
		s2/=double(i+1); //Cumulative square average
		err=Error(s,s2,i);  
      Mean << (i+1)*L << " " << s << " " << err << endl;
	}

   Mean.close();

   //Part 2: estimation of 𝜎^2 and its uncertainty
    
   M=100000;
   N=100;
   L=int(M/N);
   
   for (int i=0;i<N;i++){
      m[i]=0.;
      m2[i]=0.;
   }

   ofstream Var("variance.out");
      if(!Var.is_open()) cerr << "PROBLEM: Unable to open variance.out" << endl;
   
   for(int i=0;i<N;i++){
      s=0.;
      for(int j=0;j<L;j++){
         n=rnd.Rannyu();
         s+=(n-0.5)*(n-0.5);
      }
      m[i]=s/double(L);
      m2[i]=m[i]*m[i];
   }

   for(int i=0;i<N;i++){
      s=0.; s2=0.; err=0.;     
      for(int j=0;j<(i+1);j++){
         s+=m[j];
         s2+=m2[j];
      }  
      s/=double(i+1);
      s2/=double(i+1);
      err=Error(s,s2,i);
      Var << (i+1)*L << " " << s << " " << err << endl;
   }

   Var.close();
       
   // Part 3: 𝜒^2 test
    
   M=100;
   n=10000;
   double nM=n/M;
   int count[100]; //Counts throws
    
   ofstream Chi("chi.out");
   if(!Chi.is_open()) cerr << "PROBLEM: Unable to open chi.out" << endl;
    
   for (int t=0; t<100; t++){ //100 tests
        
      for (int i=0;i<M;i++) count[i]=0;
        
      for(int i=0; i<n; i++){
         double r=rnd.Rannyu();
         int j=r*M;
         count[j]++;
      }
        
      double chi=0.;
      for (int i=0; i<M; i++){
         double ni=double(count[i]);
         chi+=(ni-nM)*(ni-nM)/nM;
      }
      Chi << t+1 <<" "<< chi << endl;
   }
    
   Chi.close();
    
   rnd.SaveSeed();
   
   return 0;
}

double Error(double ave, double ave2, int n){
	if(n==0) return 0;
	else return sqrt((ave2-ave*ave)/n);
}