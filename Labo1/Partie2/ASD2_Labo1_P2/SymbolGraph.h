/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

#include <list>
#include "ParcoursEnLargeur.h"
#include <map>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    
    //deux conteneurs de type map qui permettent le retour efficace
    //des informations souhaitees (contains, index, name)
    std::map<unsigned int, std::string> sommet_symbole;
    std::map<std::string, unsigned int> symbole_sommet;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {         
        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        int cnt=0;
        
        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            for( auto name : names ) 
            {          
                //std::cout << name << " "; //on affiche le contenu du fichier, vous devrez commencer a remplir le graphe ici
                //test juste que name n'appartienne pas encore a la map avant l'ajout
                if(!contains(name)){
                    sommet_symbole.insert(std::pair<int, std::string>(cnt,name));
                    symbole_sommet.insert(std::pair<std::string, int>(name,cnt));
                    cnt++;
                }
            } 
            //std::cout << std::endl;
        }
        s.close();
        
        
        /* A IMPLEMENTER */
        g = new Graph(cnt);
        
        std::string nomFilm;
        
        s.open(filename);
        
        while (std::getline(s, line))
        {
            auto names = split(line, '/');
            nomFilm = *names.begin();
           
            for(auto name = names.begin(); name != names.end(); name++){
                g->addEdge(index(nomFilm), index(*name));   
            }
        }
        s.close();
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) {
        try {
            symbole_sommet.at(name);
            return true;
        }catch(const std::out_of_range& e){
            return false;
        }
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) {
         return symbole_sommet.at(name);
    }
    
    //symbole correspondant au sommet
    std::string name(int idx) {
        return sommet_symbole.at(idx);
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string & name) {
        /* A IMPLEMENTER */
        std::vector<std::string> vecteur_adjacence;
        std::list<int> liste_adjacence = g->adjacent(index(name));
        
        for (auto i = liste_adjacence.begin(); i != liste_adjacence.end();++i){
            vecteur_adjacence.push_back(this->name(*i));
        }
        return vecteur_adjacence;
    }
    
    const Graph& G() {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
