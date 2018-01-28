/* 
 * File:   TernarySearchTries.h
 * Author: guill
 *
 * Created on 26. janvier 2018, 09:56
 */

#ifndef TERNARYSEARCHTRIES_H
#define TERNARYSEARCHTRIES_H


#include <iostream>
#include <string>

using namespace std;

class TernarySearchTries {
private:
    
    
    struct Node {
        unsigned val;
        char c;
        bool derniereLettre;
        Node* left;
        Node* mid;
        Node* right;
        Node(){};
        Node(char c, unsigned val) : c(c), val(val), derniereLettre(false), right(nullptr), mid(nullptr), left(nullptr) { }
    };
    Node* root;
    
    
    Node* put(Node* x, string key, unsigned val, int d) {
        char c = key.at(d);
        if (x == nullptr){
            x = new Node(c, val);
        }
        
        if (c < x->c)                   {x->left  = put(x->left, key, val, d);}
        else if (c > x->c)              {x->right = put(x->right, key, val, d);}
        else if (d < key.length() - 1)  {x->mid   = put(x->mid, key, val, d + 1);}
        else                            {x->derniereLettre  = val;}
        return x;
    }
    
    Node* get(Node* x, string key, int d) {
        if (x == nullptr)               return nullptr;
        char c = key.at(d);
        if (c < x->c)                   return get(x->left, key, d);
        else if (c > x->c)              return get(x->right, key, d);
        else if (d < key.length() - 1)  return get(x->mid, key, d + 1);
        else                            return x;
    }
    
public:
    void put(string key, unsigned val) {
        root = put(root, key, val, 0);
    }
    
    bool contains(string key) {
        return get(key) != NULL;
    }
    
    unsigned get(string key) {
        Node* x = get(root, key, 0);
        
        return !(x == nullptr || x->derniereLettre != true);
    }
    
    TernarySearchTries() : root(nullptr) { }
    

    

    

}; 

#endif /* TERNARYSEARCHTRIES_H */

