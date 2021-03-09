![C/C++ CI](https://github.com/dadi-vardhan/SDP/workflows/C/C++%20CI/badge.svg)
# Uncertain< T > in C++ 

This is an implementation of the datatype Uncertain< T > as discussed in [1]. This data structure is developed in C++ language. 

## General Idea 

The idea is to create a datatype which implements first order uncertainty. On an abstract level, it is desired to include uncertainty in calculations easily specifically for those who are not experts in uncertainty and statistics. 

## Source Code Structure 

This is a simplified version of the actual code in c# described [here](https://github.com/klipto/Uncertainty/tree/dev/Uncertain). However, this simplified structure is capable of performing successfully in a probabilistic fashion. As progress continues, more distributions will be added to the package. 

## Install Uncertain< T > 

Simply by copying the `Uncertain_t.h` file along with `Uncertain` folder. Please keep in mind that both should be in the same directory. 

# Example 

Objective: to sample from a gaussian distribution and implement logical and mathematical operations. 

```cpp
#include <iostream>
#include "uncertain_t.h"


using namespace std; 


int main(){
    
Uncertain<double>* x = new Gaussian(2,0.03);
Uncertain<double>* y = new Gaussian(3,0.04);

Uncertain<double>* z = *x + *y; 

//check if z's new mean in range of 5.3 and 4.7 

cout << (z >= 4.7 ) << endl; 
cout << (z <= 5.3) << endl; 


// If you want to take 100 samples from the new distribution z

Sampler<double> s; 
s.Create(z); 
vector<double> samples = s.Take(100);


// Use Uncertain<T> to create Bernoulli distributions with a 0.6 probability

Uncertain<double>* b = new Bernoulli(0.6);  


// Or if you can find the distribution from which a set of samples come from 

list<double> set_of_samples = {3.0,3.0,2.0,1.0,2.0,2.0,1.0};

Uncertain<double>* distribution = new Multinomial(set_of_samples); 

//To generate samples from the set above, our Sampler<T> will use Monte Carlo Markov Chain technique (Random Walk Metropolis Hasting). 

Sampler<double> s; 
s.Create(distribution); 
vector<double> samples = s.Take(100);




return 0; 

}

```

# Test Case 

You can find a useful test case that is "Game of Life" Algorithim [here](https://github.com/dadi-vardhan/SDP/tree/master/SDP_Assignments/Game_of_life/game_of_life_Hammam). In Game of Life, a sensor is used to measure whether the surrounding points are alive or dead. In our case the sensor is noise. These values are simulated using our uncertain<T> package. Using our package, we were able to successfully tolerate the noise coming from the sensor measurements. 
    
    
## How does it work? 
The following UML diagram describes the structure of the current Uncertain<T> library. 
    
![alt text](https://github.com/dadi-vardhan/SDP/raw/master/SDP_Assignments/Uncertain_T/cpp/UML.png)


# References 

[1]J. Bornholt, T. Mytkowicz, and K. S. McKinley, “Uncertain : A First-Order Type for Uncertain Data,” in Proceedings of the 19thinternational conference on Architectural support for programminglanguages and operating systems, New York, NY, USA, Feb. 2014,pp. 51–66, doi: 10.1145/2541940.2541958.
