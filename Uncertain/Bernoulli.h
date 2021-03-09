#ifndef BERNOULLI
#define BERNOULLI

#include "RandomPrimitive.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>
using namespace std;


class Bernoulli: public RandomPrimitive<double>{

    public:
        Bernoulli(double p);
        double GetSample();
        double GetSupport();
        double Score(bool t);
        double p; 

};

Bernoulli::Bernoulli(double p){
    if(p>=0 && p <=1){
        this->p = p;
    }
}
double Bernoulli::Score(bool t){
    double prob = 0.0;
    if(t==1){
        prob = this->p; 
    }else{
        prob = 1 - this->p;
    }
    return prob; 
}

double Bernoulli::GetSample(){
    double random_prob = random_uniform(0.0,1.0);
    return (random_prob < this->p);
}

double Bernoulli::GetSupport(){
    return (double)(int)this->GetSample();
}

#endif