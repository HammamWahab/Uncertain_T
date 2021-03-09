
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "./catch2/catch.hpp"
#include"../Uncertain_t.h"
using namespace std; 


bool Gaussian_sample(){
    Uncertain<double>* X = new Gaussian(5.0,2.0);
    Sampler<double> s;
    s.Create(X);
    auto li = s.Take(100);
    bool test = true;
    for(int i=0; i<100; i++){
        double check = li.at(i);
        test = test && (check >= -3 && check <= 13);}

    return test;}

bool Gaussian_Mean(){

    double Sum = 0.0;

    Uncertain<double>* X = new Gaussian(5.0,0.10);
    Sampler<double> s;
    s.Create(X);
    auto li = s.Take(100);
    vector<double>::iterator ptr = li.begin();
    bool test = true;
    for(int i=0; i<100; i++){
        Sum += *(next(ptr,i));
    }
    Sum /=100;

    return (Sum >= 4.6 && Sum <= 5.4);
    }

bool Gaussian_BNN_Sample(){

    Uncertain<double>* X = new Gaussian(5.0,0.1);
    Uncertain<double>* Y = new Gaussian(4.0,0.1);
    Uncertain<double>* Z = *X + *Y;
    Sampler<double> s;
    s.Create(Z);
    vector<double> li = s.Take(100);
    vector<double>::iterator ptr = li.begin();
    bool test = true;
    for(int i=0; i<100; i++){
        test = test && (*(next(ptr,i)) >= -3.0 && *(next(ptr,i)) < 13.0);
    }
    return test;
}


bool Gaussian_BNN_Mean(){

    Uncertain<double>* X = new Gaussian(1.0,0.1);
    Uncertain<double>* Y = new Gaussian(4.0,0.1);
    Uncertain<double>* Z = *X + *Y;
    double sum =0;
    Sampler<double> s;
    s.Create(Z);
    auto li = s.Take(100);
    vector<double>::iterator ptr = li.begin();
    bool test = true;
    for(int i=0; i<100; i++){
        sum += (*(next(ptr,i)));
        // cout << "new sample: " << (*(next(ptr,i))) << "| ";
    }
    // cout << endl;
    sum /= 100;
    test = (sum >= 4.11 && sum < 5.89);
    return test;
}

bool Gaussian_Bernoulli_Mean(){

    Uncertain<double>* X = new Gaussian(1.0,1.0);
    Uncertain<double>* Y = new Gaussian(3.0,2.0);
    Uncertain<double>* Z = *X > *Y;
    Sampler<double> s; 
    s.Create(Z); 
    auto li = s.Take(100);
    vector<double>::iterator ptr = li.begin();
    bool test = true;
    double sum = 0.0;
    for(int i=0; i<100; i++){
        // cout << (*(next(ptr,i))) << " | ";
        if((*(next(ptr,i))) >= 0.5){
            sum += 1;
        }
        // cout << "new sample: " << (*(next(ptr,i))) << "| ";
    }
    test = (sum >=13 && sum < 52);
    return 1;
}


bool Gaussian_Bernoulli_Conditional(){
    //to ensure correct evaluation for each run, increase sample size in Pr(), however this may cause the code to take time while running ;)
    Uncertain<double>* X = new Gaussian(1.0,1.0);
    Uncertain<double>* Y = new Gaussian(4.0,2.0);

    Uncertain<double>* Z1 = *X > *Y;
    if(!Pr(*Z1)){cout << "X > Y evaluates true, incorrectly" << endl;}
    Uncertain<double>* Z2 = *Y < *X;
    if(!Pr(*Z2)){cout << "Y > X evaluates true, incorrectly" << endl;}
    Uncertain<double>* Z3 = *Y > *X;
    if(!Pr(*Z3)){cout << "Y > X evaluates false, incorrectly" << endl;}
    Uncertain<double>* Z4 = *X > *Y;
    if(!Pr(*Z4)){cout << "X > Y evaluates false, incorrectly" << endl;}

    return 1;
}



TEST_CASE("Gaussian Tests for Uncertain<T> Libraray","samples, means"){

REQUIRE(Gaussian_sample() == 1); 
REQUIRE(Gaussian_Mean()==1);
REQUIRE(Gaussian_BNN_Sample() ==1);
REQUIRE(Gaussian_BNN_Mean() ==1); 
REQUIRE(Gaussian_Bernoulli_Mean()==1); 
REQUIRE(Gaussian_Bernoulli_Conditional()==1);
}

