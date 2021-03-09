#ifndef RANDOM_PRIMITIVE
#define RANDOM_PRIMITIVE

#include"uncertain.h"
#include"IUncertainVisitor.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include<tuple>

using namespace std; 


double random_uniform(double a, double b){
    random_device generator; 
	uniform_real_distribution<double> distribution(a,b);
    double r = distribution(generator); 
    return r; 
}

template<typename T> 
class RandomPrimitive: public Uncertain<T> {
    private:
    public:
        tuple<int,T> cached;
        RandomPrimitive();
        virtual T GetSample(){return 0.0;}
        virtual double Score(T t){return 0.0;}
        T Sample(int generation);
        void Accept(IUncertainVisitor visitor){visitor.Visit(this);}

};


template<typename T>
RandomPrimitive<T>::RandomPrimitive(){
    this->cached=make_tuple(0,(T)0);
}

template<typename T>
T RandomPrimitive<T>::Sample(int generation){
    T sample;
    if(get<0>(cached)==generation){
        sample = get<1>(this->cached);
    }
    else{
        this->cached=make_tuple(generation,this->GetSample());
        sample = get<1>(this->cached);
    }
    return sample;
}

// int main(){

//     return 0; 
// }

#endif