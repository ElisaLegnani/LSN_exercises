/********************************
Numerical Simulation Laboratory
Exercise 09
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

    NewPopulation();
    PrintBestLength(0);

    for(int i=0; i<ngens; i++){
        NewGeneration(pc,pm);
        if((i+1)%100==0) cout << "Generation number " << i+1 << " - min length: " << population[0][ncities] << endl << endl;
        PrintBestLength(i+1);
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

    ReadInput >> npaths;
    cout << "- Number of paths: " << npaths << endl;

    ReadInput >> ngens;
    cout << "- Number of generations of paths: " << ngens << endl;

     ReadInput >> pc;
     ReadInput >> pm;

     cout << "- Crossover probability: " << pc*100 << "%" << endl;
     cout << "- Mutation probability: " << pm*100 << "%" << endl << endl;

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

void NewPopulation(){
    for(int i=0; i<npaths; i++){
        vector<double> random_path = RandomPath(ncities);
        population.push_back(random_path);
    }
    Sort();
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

void Sort(){
    for(int i=0; i<npaths; i++) population[i][ncities] = Length(population[i]);
    sort(population.begin(), population.end(), ComparePaths);
}

void NewGeneration(double pc, double pm){
    vector<vector<double>> new_population;

    for(int i=0; i<npaths/2; i++){
        int parent1, parent2;
        vector<vector<double>> son;

        parent1 = Selection();
        parent2 = Selection();

        son = {population[parent1], population[parent2]};

        if(rnd.Rannyu()<pc) son = Crossover(parent1,parent2);

        //Son 1

        if(rnd.Rannyu()<pm){ //Mutation 1: pair permutation of cities
            int r1=(int)rnd.Rannyu(1,ncities);
            int r2=(int)rnd.Rannyu(1,ncities);
            swap(son[0][r1],son[0][r2]);
	     }

         if(rnd.Rannyu()<pm){ //Mutation 2: inversion of city order
             int r1=(int)rnd.Rannyu(1,ncities);
             int r2=(int)rnd.Rannyu(1,ncities);

             if(r2>r1) reverse(son[0].begin()+r1, son[0].begin()+r2);
             else reverse(son[0].begin()+r2, son[0].begin()+r1);
         }

         if(rnd.Rannyu()<pm){ //Mutation 3: permutation of contiguous cities
             vector<int> r;
	         r.push_back((int)rnd.Rannyu(1,ncities));
             r.push_back((int)rnd.Rannyu(1,ncities));
             r.push_back((int)rnd.Rannyu(1,ncities));
             sort(r.begin(), r.end());

             rotate(son[0].begin()+r[0], son[0].begin()+r[1], son[0].begin()+r[2]);
         }

         //Son 2

         if(rnd.Rannyu()<pm){ //Mutation 1: pair permutation of cities
             int r1=(int)rnd.Rannyu(1,ncities);
             int r2=(int)rnd.Rannyu(1,ncities);
             swap(son[1][r1],son[1][r2]);
 	     }

          if(rnd.Rannyu()<pm){ //Mutation 2: inversion of city order
              int r1=(int)rnd.Rannyu(1,ncities);
              int r2=(int)rnd.Rannyu(1,ncities);

              if(r2>r1) reverse(son[1].begin()+r1, son[1].begin()+r2);
              else reverse(son[1].begin()+r2, son[1].begin()+r1);
          }

          if(rnd.Rannyu()<pm){ //Mutation 3: permutation of contiguous cities
              vector<int> r;
 	          r.push_back((int)rnd.Rannyu(1,ncities));
              r.push_back((int)rnd.Rannyu(1,ncities));
              r.push_back((int)rnd.Rannyu(1,ncities));
              sort(r.begin(), r.end());

              rotate(son[1].begin()+r[0], son[1].begin()+r[1], son[1].begin()+r[2]);
          }

          new_population.push_back(son[0]);
          new_population.push_back(son[1]);
      }

      population = new_population;

      Sort();
}

vector<vector<double>> Crossover(int p1, int p2){
    vector<double> path1 = population[p1];
    vector<double> path2 = population[p2];
    vector<double> new_path1(path1);
    vector<double> new_path2(path2);

    int p_cut = (int)rnd.Rannyu(1,ncities-1);

    int index = p_cut;

    for(int i=0; i<ncities; i++){
        int appo = path2[i];
        if(find(path1.begin(), path1.begin() + p_cut, appo) == path1.begin()+ p_cut){
            new_path1[index] = appo;
            index++;
        }
    }

    index = p_cut;
    for(int i=0; i<ncities; i++){
        int appo = path1[i];
        if(find(path2.begin(), path2.begin() + p_cut, appo) == path2.begin()+ p_cut){
            new_path2[index] = appo;
            index++;
        }
    }

    return {new_path1,new_path2};
}

int Selection(void){
    double p=2.;
    double r=rnd.Rannyu();
    return (int) (npaths*pow(r,p));
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

bool ComparePaths(vector<double> p1, vector<double> p2){
  return (*(p1.end()-1) < *(p2.end()-1)); //Compare lengths of paths (last element of the vector path)
}

void PrintCities(void){
    ofstream Config("positions.out");
    for(int i=0; i<ncities; i++) Config << coordinates[i][0] << " " << coordinates[i][1] <<endl;
    Config << coordinates[0][0] << " " << coordinates[0][1] << endl;
    Config.close();
}

void PrintBestPath(){
    vector<double> best_path;
    vector<vector<double>> best_coordinates;

    ofstream BestPath;
    BestPath.open("best_path.out");

    best_path = population[0];
    for(int i=0; i<ncities; i++){
        BestPath << coordinates[(int)best_path[i]][0] << " " << coordinates[(int)best_path[i]][1] << endl;
    }
    BestPath << coordinates[(int)best_path[0]][0] << " " << coordinates[(int)best_path[0]][1] << endl;

    BestPath.close();

    rnd.SaveSeed();
}

void PrintBestLength(int istep){
    vector<double> lengths;
    int half_paths = (int)(npaths/2);

    //Paths are sorted so lengths are: the best balf of the population is the first half
    for(int i=0; i<half_paths; i++) lengths.push_back(population[i][ncities]);

    ofstream BestLength;
    BestLength.open("best_length.out", ios::app);

    BestLength << istep << " " << *(lengths.begin()) << " "
        << accumulate(lengths.begin(), lengths.end(), 0.0)/half_paths << endl;

    BestLength.close();
}
