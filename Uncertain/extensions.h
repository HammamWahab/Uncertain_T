

#ifndef EXTENSIONS
#define EXTENSIONS

#include "uncertain.h"
// #include "Gaussian.h"
#include "Multinomial.h"
#include "Sampler.h"
// #include "RandomPrimitive.h"
#include "MarkovChainMonteCarloSampler.h"
#include <vector>



template<typename T>
Uncertain<T>* operator+(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist; 
    for(int i=0; i<10; i++){new_uncertain_dist.push_back(obj.GetSupport() + obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Multinomial(new_uncertain_dist);
    Uncertain<T>* new_new_uncertain = MarkovChainMonteCarlo(new_uncertain);
    delete new_uncertain; 
    return new_new_uncertain;
    }

template<typename T>
Uncertain<T>* operator-(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist; 
    for(int i=0; i<10; i++){new_uncertain_dist.push_back(obj.GetSupport() - obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Multinomial(new_uncertain_dist);
    Uncertain<T>* new_new_uncertain = MarkovChainMonteCarlo(new_uncertain);
    delete new_uncertain; 
    return new_new_uncertain;
    }

template<typename T>
Uncertain<T>* operator*(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist; 
    for(int i=0; i<10; i++){new_uncertain_dist.push_back(obj.GetSupport() * obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Multinomial(new_uncertain_dist);
    Uncertain<T>* new_new_uncertain = MarkovChainMonteCarlo(new_uncertain);
    delete new_uncertain; 
    return new_new_uncertain;
    }

template<typename T>
Uncertain<T>* operator/(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist; 
    for(int i=0; i<10; i++){new_uncertain_dist.push_back(obj.GetSupport() / (obj2.GetSupport()+0.00001));}
    Uncertain<T>* new_uncertain = new Multinomial(new_uncertain_dist);
    Uncertain<T>* new_new_uncertain = MarkovChainMonteCarlo(new_uncertain);
    delete new_uncertain; 
    return new_new_uncertain;
    }

template<typename T>
Uncertain<T>* operator>(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist;
    T count;
    for(int i=0; i<10; i++){new_uncertain_dist.push_back((obj.GetSupport() > obj2.GetSupport()));count+=(obj.GetSupport() > obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Flip(count/10);
    return new_uncertain;
    }

template<typename T>
Uncertain<T>* operator>=(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist;
    T count;
    for(int i=0; i<10; i++){new_uncertain_dist.push_back((obj.GetSupport() >= obj2.GetSupport()));count+=(obj.GetSupport() >= obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Flip(count/10);
    return new_uncertain;
    }


template<typename T>
Uncertain<T>* operator<(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist;
    T count;
    for(int i=0; i<10; i++){new_uncertain_dist.push_back((obj.GetSupport() < obj2.GetSupport()));count+=(obj.GetSupport() < obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Flip(count/10);
    return new_uncertain;
    }


template<typename T>
Uncertain<T>* operator<=(Uncertain<T>& obj,Uncertain<T>& obj2){
    list<T> new_uncertain_dist;
    T count;
    for(int i=0; i<10; i++){new_uncertain_dist.push_back((obj.GetSupport() <= obj2.GetSupport()));count+=(obj.GetSupport() <= obj2.GetSupport());}
    Uncertain<T>* new_uncertain = new Flip(count/10);
    return new_uncertain;
    }

template<typename T>
double E(Uncertain<T>& obj){

    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(25);
    double e = accumulate(samples.begin(),samples.end(),0)/25 + 1;
    return e; 
}


template<typename T>
bool operator>(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) > obj2);
    }
    sum = sum/100; 
    if(sum > 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }

template<typename T>
bool operator>=(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) >= obj2);
    }
    sum = sum/100; 
    if(sum >= 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }

template<typename T>
bool operator<(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) < obj2);
    }
    sum = sum/100; 
    if(sum >= 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }

template<typename T>
bool operator<=(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) <= obj2);
    }
    sum = sum/100; 
    if(sum >= 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }

template<typename T>
bool operator==(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) == obj2);
    }
    sum = sum/100; 
    if(sum >= 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }

template<typename T>
bool operator!=(Uncertain<T>& obj,T obj2){
    Sampler<double> s;
    s.Create(&obj);
    vector<double> samples = s.Take(100);
    double sum = 0.0;
    bool check = true;
    for(int i=0; i < 100; i++){
        sum += (samples.at(i) != obj2);
    }
    sum = sum/100; 
    if(sum >= 0.6){
        check = true; 
    }else{
        check = false; 
    }
    return check;
    }



//Hypothesis Testing
template<typename T>
bool Pr(Uncertain<T>& source, int numm_samples=10, double Prob=0.5, double Alpha =0.5, double Epsilon=0.03,
int MaxSampleSize=1,int InitSampleSize=1,int SampleSizeStep = 1){
    // cout << "1" << endl; 
    double H_0 = Prob - Epsilon; 
    double H_1 = Prob + Epsilon; 
    // Decide the log-likelihood thresholds for the test
    double Beta = Alpha;  // We are symmetric w.r.t. false positives/negatives
    double A = log(Beta / (1 - Alpha));  // Accept H_0 if the log-likelihood is <= a
    double B = log((1 - Beta) / Alpha);  // Accept H_1 if the log-likelihood is >= b

    int K = 0; 

    double WSum = 0.0; 
    double WSumTrue = 0.0; 

    Sampler<double> s; 
    s.Create(&source); 
    auto li = s.Take(10);
    double count = 0.0;
    vector<double>::iterator it = li.begin();
    for(it=li.begin(); it!=li.end(); ++it){
                if(*it >= 0.5){count++;}
            }
    count /= li.size(); 
    // cout << "2" << endl; 
    for(int num_samples=0; num_samples<InitSampleSize; num_samples++){
        if(li.at(num_samples)>0.5){
            K += 1; 
            WSumTrue += count; 
        }
        WSum += count; 
    }
    // cout << "3" << endl; 
    bool test; 
    while(numm_samples <= MaxSampleSize){
        cout << "4" << endl; 
        double Loglikelihood = WSumTrue * log(H_1/H_0) + (WSum - WSumTrue) * log((1-H_1)/(1-H_0));
        

        if(Loglikelihood >= B){test = true;}
        else if(Loglikelihood <= A){test = false;}
        else{
        for(int i=0; i<SampleSizeStep; i++){
            // cout << "5" << endl; 
            
            count = 0.0;
            auto li = s.Take(10);
            for(it=li.begin(); it!=li.end(); ++it){
                if(*it >= 0.5){count++;}
            }
            count /= li.size(); 

            if(li.at(i)>0.5){
            K += 1; 
            WSumTrue += count; 
            }
            WSum += count; 

        }
        numm_samples += SampleSizeStep;
    }
    test = false;}

    return test;


}



#endif