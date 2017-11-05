/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 * modifié le : 5 novembre 2017
 */


#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 1, ex 2 (cf. donnee)
#include "Util.h"
#include "SymbolGraph.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        if (line.find("\r") != std::string::npos)
                line.erase(line.size() - 1);
        
        auto names = split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // module
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            } 
        }
    }
    s.close();
    
    return ok;
}

int test(const string FILENAME, const char SEPARATEUR){
    SymbolGraph<DiGraph> symbolGraph(FILENAME, SEPARATEUR);
    try {
        TopologicalSort<DiGraph> topologicalSort(symbolGraph.G());
        vector<int> trie = topologicalSort.Order();

        cout << FILENAME << " est un DAG \n" << endl;

        cout << "Ordre topologique:" << endl;
        for(auto i : trie){
            cout << symbolGraph.name(i) << " ";
        }
        
        cout << "\n";
        if(checkOrder(trie, symbolGraph, FILENAME, SEPARATEUR)){
            cout << "Vérification réussie" << endl;
        }

    }catch(const TopologicalSort<DiGraph>::GraphNotDAGException& e) {
        cout << FILENAME << " n'est pas un DAG \n" << endl;

        cout << "Cycle trouvé:" << endl;
        for(auto i : e.Cycle()){
            cout << symbolGraph.name(i) << " ";
        }
        cout << symbolGraph.name(e.Cycle().front()) << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int main(int argc, const char * argv[]) {
    const char SEPARATEUR = ',';
    const string FILENAME = "prerequis.txt";
    const string FILENAME2 = "prerequis2.txt";
    cout << "Debut du test du fichier " << FILENAME << endl;
    test(FILENAME, SEPARATEUR);
    cout << "\nDebut du test du fichier " << FILENAME2 << endl;
    test(FILENAME2, SEPARATEUR);
    
    return EXIT_SUCCESS;
}
