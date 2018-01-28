/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dictionnaireSet.h
 * Author: MG
 *
 * Created on January 28, 2018, 6:20 PM
 */

#ifndef DICTIONNAIRESET_H
#define DICTIONNAIRESET_H

#include <unordered_set>
#include <string>

using namespace std;

class dictionnaireSet{
private:
    unordered_set<string> dico;
    unsigned int cpt = 0;
    
public:
    dictionnaireSet(){
        dico = unordered_set<string>();
    }
    
    void insert(string& nouveauMot){
        //dico.put(nouveauMot, cpt++);
        dico.insert(nouveauMot);
    }
    bool contains(string& mot){
        unordered_set<string>::const_iterator got = dico.find(mot);
        return got != dico.end();
    }
};

#endif /* DICTIONNAIRESET_H */

