#ifndef SAMPLER
#define SAMPLER

#include "uncertain.h"
#include "MarkovChainMonteCarloSampler.h"
#include <vector>

using namespace std;


template<typename T>
class Sampler{

    public:
        Sampler(){}
        void Create(Uncertain<T>* source);
        vector<T> Take(int size);
        Uncertain<T>* ref = new Gaussian(0,0); 
        vector<T> samples; 

};

template<typename T>
void Sampler<T>::Create(Uncertain<T>* source){
    //this to be replaced by MCMC
    // list<T> something;
    // ref = &source;
    // Uncertain<T>* refe = MarkovChainMonteCarlo(source);
    this->ref = MarkovChainMonteCarlo(source);
    // cout << "hiii new samples " << MarkovChainMonteCarlo(source)->GetSupport() << endl;
    // cout << "created sample from ref " << ref->GetSupport();
}

template<typename T>
vector<T> Sampler<T>::Take(int size){
    vector<T> taken_samples;
    for (int i = 0; i < size; i++)
    {
        taken_samples.push_back(ref->GetSupport());
        // cout << "hiii new samples " << ref->GetSupport() << endl;
    }
    return taken_samples; 

}

#endif 