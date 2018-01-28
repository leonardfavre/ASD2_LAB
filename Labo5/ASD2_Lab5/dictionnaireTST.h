/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dictionnaireTST.h
 * Author: guill
 *
 * Created on 28. janvier 2018, 10:20
 */

#ifndef DICTIONNAIRETST_H
#define DICTIONNAIRETST_H

#include "ternarySearchTries.h"
#include <string>

class dictionnaireTST{
private:
    TernarySearchTries dico;
    unsigned int cpt = 0;
    
public:
    dictionnaireTST(){
        dico = TernarySearchTries();
    }
    
    void insert(string& nouveauMot){
        dico.put(nouveauMot, cpt++);
    }
    bool contains(string& mot){
        return dico.contains(mot);
    }
};

#endif /* DICTIONNAIRETST_H */

