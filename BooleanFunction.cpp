/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   BooleanFunction.cpp
 * Author: anton
 * 
 * Created on 20 luglio 2023, 16:48
 */

#include "BooleanFunction.h"

BooleanFunction::BooleanFunction(int __variables) {
    if(__variables <= 0)
        variables = 0;
    else
        variables = __variables;
}

void BooleanFunction::askMinterms(){
    string buffer = " ";
    
    while(buffer != "$"){
        cout << "Insert minterm in P form($ for stop): ";
        cin >> buffer;
        if(buffer.length() == variables && buffer != "$" && checkMinterm(buffer)){
            cout << "Added: " << buffer << endl;
            minterms.push_back(buffer);
            n_minterms++;
        }
    }
    minterms.unique();      //clear duplicates
    minterms.sort();
}

bool BooleanFunction::addMinterm(string __minterm){
    if(__minterm.length() == variables && checkMinterm(__minterm)){
        minterms.push_back(__minterm);
        n_minterms++;
        return true;
    }
    return false;
}

void BooleanFunction::printMinterms() const{
    if(minterms.empty()){
        cout << "[EMPTY]";
        return;
    }
    cout << "You have entered these minterms:" << endl;
    for(auto i = minterms.begin(); i != minterms.end(); i++){
        cout << *i << endl;
    }
}

bool BooleanFunction::checkMinterm(string __minterm) const{
    for(auto character = __minterm.begin(); character != __minterm.end(); character++){
        if(*character != '0' && *character != '1')
            return false;
    }
    return true;
}

int BooleanFunction::countOneOccurrences(string __minterm) const{
    int cont = 0;
    for(auto character = __minterm.begin(); character != __minterm.end(); character++){
       if(*character == '1')
           cont++;
    }
    return cont;
}

int BooleanFunction::getMintermsDifference(string __minterm1, string __minterm2) const{
    int difference_count = 0;
    for(int i = 0; i < __minterm1.length(); i++){
        if(__minterm1[i] != __minterm2[i])
            difference_count++;
    }
    return difference_count;
}

Term BooleanFunction::combineMinterms(string __minterm1, string __minterm2) const{
    Term temp;
    for(int i = 0; i < __minterm1.length(); i++){
        if(__minterm1[i] != __minterm2[i]){
            __minterm1[i] = '-';
        }
    }
    temp.min = __minterm1;
    temp.used = false;
    return temp;
}

list<Term>* BooleanFunction::generateLayer(list<Term>* p, list<string>& prime_implicants){
    int class_number = variables+1;
    list<Term>* combined = new list<Term>[class_number];
    
    for(int i = 0; i < class_number-1; i++){
        for(auto min_i = (p+i)->begin(); min_i != (p+i)->end(); min_i++){
            for(auto min_ip = (p+i+1)->begin(); min_ip != (p+i+1)->end(); min_ip++){
                if(getMintermsDifference(min_i->min, min_ip->min) == 1){
                    (combined+i)->push_back(combineMinterms(min_i->min, min_ip->min));
                    min_i->used = true;
                    min_ip->used = true;
                }
            }
        }
    } 
    for(int i = 0; i < class_number; i++){
        for(auto j = (p+i)->begin(); j != (p+i)->end(); j++){
            if(j->used == false){
                prime_implicants.push_back(j->min);
            }
        }
    }
    bool stop = true;
    for(int i = 0; i < variables +1; i++){
        if(!(combined+i)->empty())
            stop = false;
    }
    if(stop)
        return nullptr;
    else
        return generateLayer(combined, prime_implicants);
}

void BooleanFunction::McCluskeyMinimize(){
    int class_number = variables + 1;
    list<Term>* p = new list<Term>[class_number];
    list<Term>* combined;
    list<string> prime_implicants;
    
    //riempie la lista di classi con i mintermini corrispondenti
    for(auto min = minterms.begin(); min != minterms.end(); min++){
        Term temp;
        temp.min = *min;
        temp.used = false;
        (p + countOneOccurrences(*min))->push_back(temp);
    }
    
    combined = generateLayer(p, prime_implicants);
  
    prime_implicants.unique();
    minimized_minterms = prime_implicants;
}

void BooleanFunction::printPrimeImplicants() const{
    if(minimized_minterms.empty()){
        cout << "[EMPTY]";
        return;
    }
    for(auto i = minimized_minterms.begin(); i != minimized_minterms.end(); i++){
        cout << *i << endl;
    }
}

