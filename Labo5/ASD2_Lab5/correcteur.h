/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   correcteur.h
 * Author: guill
 *
 * Created on 24. janvier 2018, 17:22
 */

#ifndef CORRECTEUR_H
#define CORRECTEUR_H

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>
#include <vector>

using namespace std;
using namespace chrono;


//REFLECHIR PRIVATE PUBLIC AUSSI

template <typename T>
class Correcteur {
private:
    T dictionnaire;    
        
/*    vector<string> lettreSupp(const string &word);
    vector<string> missedChar(const string &word);
    vector<string> misstyped(const string &word);
    vector<string> lettersSwapped(const string &word);*/
    
void lettreSupp(vector<string> &props, const string &word) {
    for (int i = 0; i < word.length(); i++) {
        string w = word;
        w.erase(i, 1);
        if (dictionnaire.contains(w))
            props.push_back(w);
    }
}

void missedChar(vector<string> &props, const string &word) {    
    for (int i = 1; i <= word.size() + 1; i++) {
        // On split le mot en 2, à chaque interval de lettre
        string pre = word.substr(0, i);
        //cout << "pre: " << pre << endl;
        string post;
        if (i < word.size() + 1)
            post = word.substr(i, word.size() - i);
        //cout << "post: " << post << endl;
        for (char c = 'c'; c <= 'z'; c++) {
            string prop = pre + c + post;
            if (dictionnaire.contains(prop))
                props.push_back(prop);
        }
    }   
}

void misstyped(vector<string> &props, const string &word) {    
    for (int i = 0; i < word.size(); i++) {
        string prop = word;
        for (char c = 'a'; c <= 'z'; c++) {
            prop.replace(i, 1, 1, c);
            //cout << prop << endl;
            if (dictionnaire.contains(prop))
                props.push_back(prop);
        }
    }
}

void lettersSwapped(vector<string> &props, const string &word) {    
    for (int i = 0; i < word.size() - 1; i++) {
        char c1 = word.at(i);
        char c2 = word.at(i + 1);
        
        string pre = word.substr(0, i);
        string post;
        if (i < word.size() - 2)
            post = word.substr(i + 2, word.size() - 1);
                
        //cout << pre + c2 + c1 + post << endl;
        string prop = pre + c2 + c1 + post;
        if (dictionnaire.contains(prop))
            props.push_back(prop);
    }
}   
    
//Constructeur
public:
    Correcteur(string nomFichier){
        long int compteurMot = 0;
        //gestion tu temps
        steady_clock::time_point t1 = steady_clock::now();
        
        cout << "Chargement du dictionaire ..." << endl;
        //a reflecchir poru la taille
        ifstream fichier;
        //ong int compteurMot = 0;
        fichier.open(nomFichier);
        
        if(fichier){
            string nouveauMot;
            string motFormate;
            
            while(!fichier.eof()){
                fichier >> nouveauMot;
                motFormate = formatage(nouveauMot);
                //gestion fin de ficher à vérifier
                //pour gérer des à la ligne en fin de fichier ou des mots qui n'en sotn pas
                if(motFormate.empty()){
                    continue;
                }
                dictionnaire.insert(motFormate);
                ++compteurMot;
                nouveauMot = "";
            }
        }
        fichier.close();
        cout  <<  compteurMot << " mots sont chargé dans le dictionnaire" << endl;
        //fin gestion du temps d'ouverture et enregistrement du dico
        steady_clock::time_point t2 = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout << "Dictionnaire chargé en " << time_span.count() << " secondes" << endl << endl; 
    }
    
    void correction( string fichierAtester){
        
        steady_clock::time_point t1 = steady_clock::now();
        cout << "Debut du test de " << fichierAtester << endl;
        ifstream fichier;
        
        fichier.open(fichierAtester);
        ofstream corrections;
        string nom = "out_" + fichierAtester;
        corrections.open(nom , ios::out);
        
        if(fichier){
            string mot;
            string motFormate;
            while(!fichier.eof()){
                fichier >> mot;

                motFormate = formatage(mot);
                if(motFormate.empty()){
                    continue;
                }
                
                if(!dictionnaire.contains(motFormate)){
                    corrections << "*" << motFormate << endl;
                }
                //AJOUTER ICI LES APPELLES DES FCT DE CORRECTIONS
                ///////////////////////////////////////////////
                //////////////////////////////////////////////////
                vector<string> props;
                lettreSupp(props, motFormate);
                for (int i = 0; i < props.size(); i++)
                    corrections << "1:" << props[i] << endl;  
                props.clear();
                missedChar(props, motFormate);
                for (int i = 0; i < props.size(); i++)
                    corrections << "2:" << props[i] << endl; 
                props.clear();
                misstyped(props, motFormate);
                for (int i = 0; i < props.size(); i++)
                    corrections << "3:" << props[i] << endl; 
                props.clear();
                lettersSwapped(props, motFormate);
                for (int i = 0; i < props.size(); i++)
                    corrections << "4:" << props[i] << endl;
            }
        }
        fichier.close();
   
        steady_clock::time_point t2 = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout << "fin du test en " << time_span.count() << " secondes" << endl;
    }
    
    string formatage (string aFormater){
        //Attention manque apostrophe
        string motTemp = "";
        char c;
        //cout << "--" << endl;
        //cout << "Puis la : "  << aFormater << endl;
        for(int i = 0; i < aFormater.size(); ++i){
            c = tolower(aFormater.at(i));           
            if((c >= 'a' && c <= 'z') || (c == '\'' && aFormater.size() > 1)){
                motTemp += c;               
            }
        }
        return motTemp;
    }
};


#endif /* CORRECTEUR_H */

