/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "correcteur.h"

using namespace std;

/*
template <typename T>
vector<string> Correcteur<T>::lettreSupp(const string &word) {
    vector<string> props;
    for (int i = 0; i < word.length(); i++) {
        string w = word;
        string prop = w.erase(i, 1);
        if (dictionnaire.contains(w))
            dictionnaire.insert(w);
    }
    return props;
}

template <typename T>
vector<string> Correcteur<T>::missedChar(const string &word) {
    vector<string> props;
    
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
                dictionnaire.insert(prop);
        }
    }   
    return props;
}

template <typename T>
vector<string> Correcteur<T>::missTyped(const string &word) {
    vector<string> props;
    
    for (int i = 0; i < word.size(); i++) {
        string prop = word;
        for (char c = 'a'; c <= 'z'; c++) {
            prop.replace(i, 1, 1, c);
            //cout << prop << endl;
            if (dictionnaire.contains(prop))
                dictionnaire.insert(prop);
        }
    }
    return props;    
}

template <typename T>
vector<string> Correcteur<T>::lettersSwapped(const string &word) {
    vector<string> props;
    
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
            dictionnaire.insert(prop);
    }
    return props;
}    
*/

template <typename T>
void Correcteur<T>::lettreSupp(vector<string> &props, const string &word) {
    for (int i = 0; i < word.length(); i++) {
        string w = word;
        w.erase(i, 1);
        if (dictionnaire.contains(w))
            props.push_back(w);
    }
}

template <typename T>
void Correcteur<T>::missedChar(vector<string> &props, const string &word) {    
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

template <typename T>
void Correcteur<T>::misstyped(vector<string> &props, const string &word) {    
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

template <typename T>
void Correcteur<T>::lettersSwapped(vector<string> &props, const string &word) {    
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