#ifndef UNCERTAIN_T_H
#define UNCERTAIN_T_H


#include <iostream>
#include <list> 
#include <iterator> 

using namespace std; 


template<typename T>
class Uncertain{
    private:
    public:
        Uncertain(){}
        list<T> distribution;
        virtual T GetSupport(){return 0.0;};
        list<T> Support();
        bool operator==(Uncertain<T> const &obj);
        bool operator!=(Uncertain<T> const &obj);
        bool operator>(Uncertain<T> const &obj);
        bool operator>=(Uncertain<T> const &obj);
        bool operator<(Uncertain<T> const &obj);
        bool operator<=(Uncertain<T> const &obj);
        // Uncertain<T> operator+(Uncertain<T> obj);

};

// need to add operator +, -, *, / overloading here 


template<typename T>
list<T> Uncertain<T>::Support(){
    list<T> s; 
    for(int i=0; i<5; i++){
    s.push_back(this->GetSample());
    }
    return s;
}


template<typename T>
bool Uncertain<T>::operator==(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support == this->Support());
}

template<typename T>
bool Uncertain<T>::operator!=(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support != this->Support());
}

template<typename T>
bool Uncertain<T>::operator>(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support > this->Support());
}

template<typename T>
bool Uncertain<T>::operator>=(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support >= this->Support());
}

template<typename T>
bool Uncertain<T>::operator<(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support < this->Support());
}

template<typename T>
bool Uncertain<T>::operator<=(Uncertain<T> const &obj){
    list<T> obj_support = obj.Support(); 
    return (obj_support <= this->Support());
}

// template<typename T>
// Uncertain<T> operator+(Uncertain<T> &obj1, Uncertain<T> &obj2 ){
//      return obj1;};




//main for testing 
// int main(){

//     return 0;
// }



#endif