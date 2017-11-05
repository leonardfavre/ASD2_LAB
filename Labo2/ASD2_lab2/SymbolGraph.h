/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_OC2017_H
#define	SYMBOLGRAPH_OC2017_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    std::map<std::string,int> symbolTable;
    std::vector<std::string> keys;
    Graph* g;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
       
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename, char separateur) {         
        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        int cnt=0; 

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            if (line.find("\r") != std::string::npos)
                line.erase(line.size() - 1);
            auto names = split(line,separateur);
            for( auto name : names ) 
                if(!contains(name))
                    symbolTable[name] = cnt++;
        }
        s.close();
        
        keys.resize(cnt);
        for(const auto& pair : symbolTable)
            keys[pair.second] = pair.first; 
        
        g = new Graph(cnt);
        
        s.open(filename);
        while (std::getline(s, line))
        {
            if (line.find("\r") != std::string::npos)
                line.erase(line.size() - 1);
            
            auto names = split(line, separateur);
           
            int v = symbolTable[names[0]];
            for( size_t i = 1; i < names.size(); ++i ) {
                int w = symbolTable[names[i]];
                g->addEdge(v,w);
            }
        }
        s.close();
        *g = g->reverse();
        
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        return symbolTable.find(name) != symbolTable.end();
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
        
        return symbolTable.at(name);
    }
    
    //symbole correspondant au sommet
    std::string name(int idx) const {
        return keys[idx];
    }
    
    std::vector<std::string> adjacent(const std::string & name) const
    {
        if(!contains(name)) 
            return std::vector<std::string>(0);
        
        auto& adjIdx = g->adjacent( index(name));
        int N = adjIdx.size();
        std::vector<std::string> adjStr(N);

        std::transform(adjIdx.cbegin(), adjIdx.cend(), adjStr.begin(), [&](int i){ return this->name(i); } );
        
        return adjStr; 
    }
    
    const Graph& G() const {
        return *g; 
    }
    //MODIF
    void affichage(){
        for(int i = 0; i < g->V(); ++i) {
            list<int> f = g->adjacent(i);
                cout << keys[i] << "(" << i << "): ";
                for (int j : g->adjacent(i)) {
                        cout << keys[j] << " ";
                }
            cout << "\n";


        }  
    }
    
};

#endif	/* SYMBOLGRAPH_OC2017_H */

