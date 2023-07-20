/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: anton
 *
 * Created on 20 luglio 2023, 16:26
 */

#include <iostream>
#include "BooleanFunction.h"

using namespace std;


int main(int argc, char** argv) {
    int variables;
    do{
        cout << "Insert variable's number(greater than 0): ";
        cin >> variables;
        cout << endl;
    }while(variables <= 0);
    cin.ignore(1);
    
    BooleanFunction funzione(variables);
    
    funzione.askMinterms();
    funzione.printMinterms();
    funzione.McCluskeyMinimize();
    cout << "Function's prime implicants are:" << endl;
    funzione.printPrimeImplicants();
 
    return 0;
}

