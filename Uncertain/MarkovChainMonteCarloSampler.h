#ifndef MCMC
#define MCMC

#include <iostream>
#include "uncertain.h"
#include "Gaussian.h"
#include "Multinomial.h"
#include <random>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std; 



template<typename T>
T likelihood(T &mean,T &sigma, vector<T> &distrib){

    T a,b,c,sum; 
    //dont forget to change 3 into NUM_OF_SAMPLES
    for(int i=0; i < distrib.size(); i++){
    a =  -log(sigma * sqrt(2* M_PI) );
    b = (distrib.at(i) - mean)*(distrib.at(i) - mean);
    c = 2*sigma*sigma; 
    sum +=  a - (b/c);
    }

    return sum; 
}

      
// float random_uniform(float a, float b){
//     random_device generator; 
// 	uniform_real_distribution<float> distribution(a,b);
//     float r = distribution(generator); 
//     return r; 
// }



template<typename T>
Uncertain<T>* MarkovChainMonteCarlo(Uncertain<T>* source){

    // cout << "This is gonna be interesting to build" << endl;
    vector<T> samples;
    vector<T> accepted; 
    vector<T> rejected; 
    T mean = 0.0;
    T sigma = 0.05;
    for(int i=0; i<10; i++){
        samples.push_back(source->GetSupport());
        mean += samples.at(i)/10;}

    //initial guess is the mean of the provided samples
    T current_sample = mean;
    T current_sample_likelihood = likelihood(current_sample,sigma,samples);
    //generate new sample and estimate it's likelihood
    for(int i=0; i<100; i++){
    T new_sample = current_sample + Gaussian(0.0,sigma).GetSample();
    // T new_sigma = sigma + Gaussian(0.0,sigma).GetSample();
    // cout << "Current Sample: " << current_sample << endl;
    // cout << "Current Sample likelihood: " << current_sample_likelihood << endl;
    T new_sample_likelihood = likelihood(new_sample,sigma,samples);

    // cout << "New sample: " << new_sample << endl;
    // cout << "new sample likelihood: " << new_sample_likelihood << endl; 

    // calculate the acceptance ratio
    T A = new_sample_likelihood/current_sample_likelihood;
    float r = random_uniform(0.0,1.0);
    if(A>1 || exp(new_sample_likelihood - current_sample_likelihood)){
        current_sample = new_sample;
        current_sample_likelihood = new_sample_likelihood;
        accepted.push_back(new_sample);
        // cout << "new sample accepted" << endl;
    }else{

        rejected.push_back(new_sample);
        // cout << "new sample rejected" << endl;
    }
    
    }
    vector<T> burnin; 
    T new_mean = 0.0;
    for(int i=round(accepted.size()*0.25); i < accepted.size(); i++){
        burnin.push_back(accepted.at(i)); 
        // cout << accepted.at(i) << endl; 
        new_mean += accepted.at(i);
    }
    new_mean /= burnin.size();

    // cout << "new mean " <<new_mean << endl; 
    list<T> tmp_burnin;
    for(int i=0; i<burnin.size(); i++){
        tmp_burnin.push_back(burnin.at(i));
        // cout << "tmp burnin: " << burnin.at(i) << "| " ; 
    }
    // cout << endl;
    // Uncertain<T>* brand_new_uncertain = new Gaussian(new_mean,sigma);
    Uncertain<T>* brand_new_uncertain = new Multinomial(tmp_burnin);
    // cout << "from inside mcmc " << brand_new_uncertain->GetSupport()<< endl;
    // cout << "I should return the new uncertain" << endl; 
    return brand_new_uncertain;
}


#endif




// int main(){

//     Uncertain<double> *x = new Gaussian(10,0.5);
//     // MarkovChainMonteCarloSampler<double> s(x);
//     // auto t = MarkovChainMonteCarlo(*x);
//     Uncertain<double> *y = MarkovChainMonteCarlo(*x);

//     cout << y->GetSupport() << endl; 

//     return 0;
// }