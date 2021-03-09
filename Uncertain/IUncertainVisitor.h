#include <iostream>
#include "RandomPrimitive.h"
#include"uncertain.h"

using namespace std; 



class IUncertainVisitor{
    public:
        template<class Q> double Visit(Q &erp){}
};


// int main(){

//     RandomPrimitive<double> erp; 
//     cout << erp.Sample(3) << endl; 
//     return 0;
// }