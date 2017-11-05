/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <list>
#include <vector>
#include <exception>

//Ajout
#include "ParcoursEnProfondeur.h"

template < typename GraphType >
class TopologicalSort {
private:
    DFS<GraphType>* g;
    vector<int> trie;
    
public:
    //constructeur
    TopologicalSort(const GraphType & g) {
        /* vous devez verifier la presence d'un cycle, auquel cas il faut lancer une  GraphNotDAGException*/
        DirectedCycle<GraphType> directedCycle(g);
        
        try{
            if (directedCycle.HasCycle()){
                list<int> cycle = directedCycle.Cycle();
                
                throw GraphNotDAGException(cycle);
            }
        }
        catch(const GraphNotDAGException& e){
            throw e;
        }
        this->g = new DFS<GraphType> (g);
    }
    
    //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
        g->visitGraph([](int v){}, [this](int v){
            trie.push_back(v);
        });
        std::reverse(trie.begin(),trie.end());
        return trie;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
            
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
