/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: guill
 *
 * Created on 18. janvier 2018, 13:38
 */
#include <iostream>
#include <cstdlib>


#include "correcteur.h"
#include "TernarySearchTries.h"
#include "dictionnaireTST.h"

using namespace std;


int main(int argc, char** argv) {
    //Correcteur<dictionnaireSet> dicoSet("dictionary.txt");
    Correcteur<dictionnaireTST> dicoTst("dictionary.txt");
    
    dicoTst.correction("input_lates.txt");
    //dicoSet.correction("input_lates.txt");
    
    dicoTst.correction("input_sh.txt");
    //dicoSet.correction("input_sh.txt");
    
    dicoTst.correction("input_simple.txt");
    //dicoSet.correction("input_simple.txt");
    
    dicoTst.correction("input_wikipedia.txt");
    //dicoSet.correction("input_wikipedia.txt");
    return 0;
}

