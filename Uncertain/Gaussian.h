#ifndef GAUSSIAN
#define GAUSSIAN

#include "RandomPrimitive.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>
using namespace std;


//function to generate random samples from a uniform distribution 
// double random_uniform(double a, double b){
//     random_device generator; 
// 	uniform_real_distribution<double> distribution(a,b);
//     double r = distribution(generator); 
//     return r; }


// define the Gaussian class 
class Gaussian: public RandomPrimitive<double>{

    protected:
        double mu, std_dev;

    public:
        Gaussian(double mean=0.0, double stdev=1.0);
        double Likelihood(double t, double mu, double stdev);
        double NextGaussian(); 
        double Score(double t); 
        double GetSample(); 
        double GetSupport();
};



Gaussian::Gaussian(double mean, double stdev){
    this->mu = mean;
    this->std_dev = stdev;
}

double Gaussian::Likelihood(double t, double mu, double stdev){
    double a = 1.0/(stdev*sqrt(2*M_PI));
    double b = exp(-pow(t-mu,2)/(2*stdev*stdev));
    return a*b; 
}

double Gaussian::NextGaussian(){
    static const double epsilon = std::numeric_limits<double>::min();
    static const double two_pi  = 2.0*3.141592653;
    double z0,z1,mag;
    double u1,u2;
    do
    {
        u1 = random_uniform(0,1); 
        u2 = random_uniform(0,1); 
    }
    while (u1 <= epsilon);
    mag = this->std_dev * sqrt(-2.0*log(u1));
    z0 = mag * cos(two_pi * u2);
    z1 = mag * sin(two_pi * u2);
    double sample = (double) z0; 
    return sample;
}

double Gaussian::Score(double t){
    double a = 1.0/(this->std_dev*sqrt(2*M_PI));
    double b = exp(-pow(t-this->mu,2)/(2*this->std_dev*this->std_dev));
    return a*b;
}

double Gaussian::GetSample(){
    return this->NextGaussian()*this->std_dev + this->mu;
}

double Gaussian::GetSupport(){
    // to be modified
    // list<double> something;
    // for(int i=0; i<100; i++){
    // something.push_back(this->GetSample());
    // }
    // cout << "infinite support" << endl; 
    // cout << "accumulate " << (accumulate(begin(something),end(something),0.0))<<endl;
    // return something; 
    // cout << "Infinite Gaussian Support" << endl; 
    return this->GetSample();
}

// int main(){
//     Uncertain<double> *bp = new Gaussian(1,0.1);
//     bp->GetSupport();
//     Gaussian x(10,2);
//     cout << x.Score(10) << endl; 
//     return 0; 
// }

#endif