/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   BooleanFunction.h
 * Author: anton
 *
 * Created on 20 luglio 2023, 16:48
 */

#ifndef BOOLEANFUNCTION_H
#define BOOLEANFUNCTION_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

typedef struct{
        string min;
        bool used;
} Term ;

class BooleanFunction {
public:
    //constructor
    BooleanFunction(int __variables);
    virtual ~BooleanFunction(){};
    
    //asks P-Form minterms and fills into minterms
    void askMinterms();
    
    //adds a single minterm
    bool addMinterm(string __minterm);
    
    //prints minterms list into the stdout
    void printMinterms() const;
    
    //prints the boolean function's prime implicants(after calling McCluskeyMinimize
    void printPrimeImplicants() const;
    
    //fills minimized_minterms with the McCluskey algorithm
    void McCluskeyMinimize();
    
private:
    list<string> minterms;
    int variables;
    int n_minterms = 0;
    list<string> minimized_minterms;
    
    //McCluskey's definitions
    bool checkMinterm(string __minterm) const;
    int countOneOccurrences(string __minterm) const;
    int getMintermsDifference(string __minterm1, string __minterm2) const;
    Term combineMinterms(string __minterm1, string __minterm2) const;
    list<Term>* generateLayer(list<Term>* p, list<string>& prime_implicants);
};

#endif /* BOOLEANFUNCTION_H */

