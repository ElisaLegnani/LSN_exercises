/********************************
Numerical Simulation Laboratory
Exercise 10.1
Elisa Legnani
*********************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include "random.h"
#include "TSP.h"

using namespace std;

int main(int argc, char *argv[]){

    Input();
    PrintBestLength(0);

    for (int i=0; i<tsteps; i++){
        Reset();

        for (int j=0; j<nsteps; j++){
            Metropolis();
        }

        FindBestLength();
        PrintBestLength(i+1);

        if ((i+1)%20==0){
            cout << "Temperature step number " << i+1 << ", T=" << temp << endl << "  min length: "<< bestlength <<endl;

            alpha=double(accepted)/double(attempted);
            e=(0.5-alpha)/0.5;
            cout <<"  acceptance rate: " << alpha << endl << endl ;
        }

        temp*=trate;
        nsteps+=100;
    }

    PrintBestPath();

    return 0;
}

void Input(void){

    ifstream seedout("seed.out");
    bool checkseed=seedout.is_open();
    seedout.close();

    if(checkseed) rnd.SetSeed("seed.out");
    else rnd.SetSeed();

    ifstream ReadInput;

    cout << "Travelling Salesman Problem " << endl;
    cout << "Genetic Algorithm "<< endl << endl;

    ReadInput.open("input.dat");

    ReadInput >> ncities;
    ReadInput >> config;

    cout << "The program evaluates the shortest path"<< endl;
    cout << "  among " << ncities << " cities" << endl;
    if(config=="circle"){
        cout << "  on a circumference with radius=1" << endl << endl;
        Circumference();
    } else if(config=="square"){
        cout << "  inside a square with side=1" << endl << endl;
        Square();
    } else {
        cout << "PROBLEM: Insert the cities configuration: 'circle' or 'square'"<< endl << endl;
    }

    PrintCities();

    ReadInput >> temp;
    ReadInput >> trate;
    ReadInput >> tsteps;
    ReadInput >> nsteps;

    cout << "- Initial temperature: " << temp << endl;
    cout << "- Temperature decay rate: " << trate << endl;
    cout << "- Number of temperature steps: " << tsteps << endl;
    cout << "- Number of (target) Metropolis steps: " << nsteps << endl << endl;

    
    double d=nsteps-100*(tsteps-1);
    d=nsteps/d;
    nsteps=int(nsteps/d);

     path=RandomPath(ncities);
     bestpath=path;
     bestlength=Length(path);

     ReadInput.close();
}

void Circumference(void){
    for(int i=0; i<ncities; i++){
        double theta=rnd.Rannyu()*2*M_PI;
        double x=cos(theta);
        double y=sin(theta);
        coordinates.push_back({x,y});
    }
}

void Square(void){
    for(int i=0; i<ncities; i++){
        double x=rnd.Rannyu();
        double y=rnd.Rannyu();
        coordinates.push_back({x,y});
    }
}

vector<double> RandomPath(int ncities){
    vector<double> path;

    path.push_back(0.0);
    path.push_back(1 + rand()%(ncities-1));

    while(path.size() != ncities){
        int random = 1 + rand()%(ncities-1);
        if(find(path.begin(), path.end(), random) == path.end()) path.push_back(random);
    } //Every city is visited only once and all cities are visited

    path.push_back(0.0); //Extra space to store the length of the path

    return path;
}

vector<double> Mutation(vector<double> path){
    vector<double> new_path = path;

    int r = (int)rnd.Rannyu(0,3);

    if(r==0){ //Mutation 1: pair permutation of cities
        int r1=(int)rnd.Rannyu(1,ncities);
        int r2=(int)rnd.Rannyu(1,ncities);
        swap(new_path[r1],new_path[r2]);
    }

    if(r==1){ //Mutation 2: inversion of city order
        int r1=(int)rnd.Rannyu(1,ncities);
        int r2=(int)rnd.Rannyu(1,ncities);

        if(r2>r1) reverse(new_path.begin()+r1, new_path.begin()+r2);
        else reverse(new_path.begin()+r2, new_path.begin()+r1);
    }

    if(r==2){ //Mutation 3: permutation of contiguous cities
        vector<int> r;
        r.push_back((int)rnd.Rannyu(1,ncities));
        r.push_back((int)rnd.Rannyu(1,ncities));
        r.push_back((int)rnd.Rannyu(1,ncities));
        sort(r.begin(), r.end());

        rotate(new_path.begin()+r[0], new_path.begin()+r[1], new_path.begin()+r[2]);
    }
    return new_path;
}

void Reset(){
    attempted=0;
    accepted=0;
    beta=1./temp;
    tstep++;
}

void Metropolis(void){
    vector<double> y=Mutation(path);

    //Probability to accept
    double deltaL=Length(y)-Length(path);
    double q=exp(-beta*deltaL);
    double A=min(1.,q);

    //Accept?
    double r=rnd.Rannyu();
    if (r<=A){
        path=y;
        accepted++;
    }
    attempted++;
}

void FindBestLength(void){
    double length=Length(path);
    if(length<bestlength){
        bestpath=path;
        bestlength=length;
    }
}

double Distance(vector<double> c1, vector<double> c2){
    double d2=0.;
    for(int i=0 ; i<2; i++) d2 = d2 + pow(c1[i]-c2[i],2);
    return sqrt(d2);
}

double Length(vector<double> path){
    double sum=0.;
    for(int i=0; i<ncities; i++){
        sum = sum + Distance(coordinates[(int)path[i]],coordinates[(int)path[(i+1)%ncities]]);
    }
    return sum;
}

void PrintCities(void){
    ofstream Config("positions.out");
    for(int i=0; i<ncities; i++) Config << coordinates[i][0] << " " << coordinates[i][1] <<endl;
    Config << coordinates[0][0] << " " << coordinates[0][1] << endl;
    Config.close();
}

void PrintBestPath(){
    ofstream BestPath;
    BestPath.open("best_path.out");

    for(int i=0; i<ncities; i++){
        BestPath << coordinates[(int)bestpath[i]][0] << " " << coordinates[(int)bestpath[i]][1] << endl;
    }
    BestPath << coordinates[(int)bestpath[0]][0] << " " << coordinates[(int)bestpath[0]][1] << endl;

    BestPath.close();

    rnd.SaveSeed();
}

void PrintBestLength(int tstep){
    ofstream BestLength;
    BestLength.open("best_length.out", ios::app);

    BestLength << tstep << " " << temp << " " << bestlength << endl;

    BestLength.close();
}
