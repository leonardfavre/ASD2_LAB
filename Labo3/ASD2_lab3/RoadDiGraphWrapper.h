/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoadDiGraphWrapper.h
 * Author: guill
 *
 * Created on 30. novembre 2017, 13:38
 */

#ifndef ROADDIGRAPHWRAPPER_H
#define ROADDIGRAPHWRAPPER_H

#include "RoadNetwork.h"
#include "EdgeWeightedDigraph.h"

using namespace std;

template <typename Fonction>
class RoadDiGraphWrapper {
private:
    RoadNetwork rn;
    Fonction coutCalcul; 
    bool isPlusCourt;
    
public:
    typedef WeightedDirectedEdge<double> Edge;
    
    RoadDiGraphWrapper(RoadNetwork& rn, Fonction f, bool isPlusCourt): rn(rn), coutCalcul(f), isPlusCourt(isPlusCourt){}
    
    //nombre de sommet
    int V() const {
        return int(rn.cities.size());
    }
    
    //applique une fonction à toutes les arretes adjacentes à arrete
    template<typename Func>
    void forEachAdjacentEdge(int depart, Func fonction) const{ 
        std::vector<int> e = rn.cities.at(depart).roads;
        for (int i = 0; i < e.size(); i++) {
            std::pair<int, int> p = rn.roads.at(e.at(i)).cities;
            int arrivee = (p.first == depart ? p.second:p.first);
            
            if (isPlusCourt)
                fonction(WeightedDirectedEdge<double>(depart,arrivee,rn.roads.at(e.at(i)).length));
            else
                fonction(WeightedDirectedEdge<double>(depart,arrivee,coutCalcul(rn.roads.at(i))));
        }
    };
    
    //applique une fonction à tous les sommets
    template<typename Func>
    void forEachVertex(Func fonction) const{
        for(int ville = 0; ville < rn.cities.size(); ++ville){
            fonction(ville);
        }
    }
};



#endif /* ROADDIGRAPHWRAPPER_H */