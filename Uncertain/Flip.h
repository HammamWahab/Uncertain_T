#ifndef FLIP
#define FLIP

#include "RandomPrimitive.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>
using namespace std;

class Flip: public RandomPrimitive<double>{

    public:
        Flip(double p);
        double GetSample();
        double GetSupport();
        double Score(bool t);
        double p; 

};

Flip::Flip(double p){
    if(p>=0 && p <=1){
        this->p = p;
    }
}
double Flip::Score(bool t){
    double prob = 0.0;
    if(t==1){
        prob = this->p; 
    }else{
        prob = 1 - this->p;
    }
    return prob; 
}

double Flip::GetSample(){
    double random_prob = random_uniform(0.0,1.0); 
    
    return (random_prob < this->p);
}

double Flip::GetSupport(){
    return (double)(int)this->GetSample();
}

#endif