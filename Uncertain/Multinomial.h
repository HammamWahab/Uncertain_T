

#include "RandomPrimitive.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>
#include <iterator>
#include <list> 

using namespace std;

// double random_uniform(double a, double b){
//     random_device generator; 
// 	uniform_real_distribution<double> distribution(a,b);
//     double r = distribution(generator); 
//     return r; 
// }

#ifndef MULTINOMIAL
#define MULTINOMIAL







class Multinomial: public RandomPrimitive<double>{
    protected:
        list<double> options;
    public: 
        Multinomial(list<double> x){
            this->options = x;
            }
        double GetSupport(){return this->GetSample();}
        double Score(double t){
            // double probability = (double)count(options.begin(),options.end(),3.0)/options.size();
            double probability; 
            double count = 0;
            list<double>::iterator it; 
            for(it=this->options.begin(); it!=this->options.end(); ++it){
                if(this->Score(*it) < t){count++;}
            }
            probability = (double) count/this->options.size();
            return probability; 
        }
        double GetSample(){
            //tmp solution 
            vector<double> tmp_options; 
            double p = 0.0;
            double value = (int)random_uniform(0,options.size()-1);
            double sample = 0.0;
            list<double>::iterator it; 
            for(it=this->options.begin(); it!=this->options.end(); ++it){
            tmp_options.push_back(*it);}
            return tmp_options.at(value); 
        }
};


// int main(){

//     list<double> l;
//     for (int i = 0; i < 10; ++i) 
//     { 
//         l.push_back(i); 
//     } 

//     Multinomial x = l;
//     cout << x.GetSample() << endl;
//     return 0;
// }

#endif