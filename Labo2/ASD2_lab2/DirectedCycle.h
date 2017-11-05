/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

using namespace std;

template<typename GraphType>
class DirectedCycle {
private:
    vector<bool> marque;
    vector<bool> empile;
    vector<bool> listeDeCycle;
    bool trouveCycle = false;
    list<int> cycle;    
    
	
public:
    //constructeur
    DirectedCycle(const GraphType& g) {
        marque.resize(g.V());
        empile.resize(g.V());
        listeDeCycle.resize(g.V());
                
        for (int i = 0; i < g.V(); i++) {
            DetectionCycle(i, g);
        }
        
        for(int i = 0; i < listeDeCycle.size(); i++){
            if (listeDeCycle[i])
                cycle.push_back(i);
        }        
    }

    //indique la presence d'un cycle
    bool HasCycle() {
        return trouveCycle;
    }

    //liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
        return cycle;
    }
private:
    //Algorithme du cours
    bool DetectionCycle(int v, const GraphType& g){
        marque[v] = true;
        empile[v] = true; 

        for(auto w : g.adjacent(v)){
            if(trouveCycle){
                return true; 
            }
            else if (!marque[w]){
                DetectionCycle(w, g);
            }
            else if(empile[w]){
                trouveCycle = true;
                listeDeCycle.insert(listeDeCycle.begin(), empile.begin(), empile.end());
            }
        }
        empile[v] = false;
    }
	
};

#endif
