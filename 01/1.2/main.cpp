/****************************************************************
Numerical Simulation Laboratory
Exercise 01.2
Elisa Legnani
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   //Random number generator
   Random rnd;
	rnd.SetSeed();
    
	int M=10000; //Number of throws
	int N[4]={1,2,10,100};

   ofstream Std("dice_std.out");   
   if(!Std.is_open()) cerr << "PROBLEM: Unable to open dice.out" << endl;
   ofstream Exp("dice_exp.out");   
   if(!Exp.is_open()) cerr << "PROBLEM: Unable to open dice_exp.out" << endl;
   ofstream Lor("dice_lor.out");   
   if(!Lor.is_open()) cerr << "PROBLEM: Unable to open dice_lor.out" << endl;
	
	for(int i=0;i<4;i++){
	   
      for(int j=0;j<M;j++){
         double s=0.; //Standard dice
         double e=0.; //Exponential dice
         double l=0.; //Lorentzian dice

         for(int k=0;k<N[i];k++){
            s+=int(rnd.Rannyu(1.,7.));
            e+=rnd.Exponential(1.);
            l+=rnd.Lorentz(0.,1.);
         }

         s/=double(N[i]);
         e/=double(N[i]);
         l/=double(N[i]);
            
         Std << s << endl; 
         Exp << e << endl; 
         Lor << l << endl; 
      }	
	}

   Std.close();
   Exp.close(); 
   Lor.close();
    
   rnd.SaveSeed();
    
   return 0;
}