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

template <typename Fonction>
class RoadDiGraphWrapper {
private:
    RoadNetwork rn;
    Fonction coutCalcul; 
    
public:
    typedef WeightedDirectedEdge<double> Edge;
    
    // Construction du Wrapper
    RoadDiGraphWrapper(RoadNetwork& rn, Fonction f): rn(rn), coutCalcul(f){}
    
    //nombre de sommet
    int V() const {
        return int(rn.cities.size());
    }
    
    //applique une fonction à toutes les arretes adjacentes à arrete
    template<typename Func>
    void forEachAdjacentEdge(int arrete, Func fonction) const{
    //void forEachEdge(int arrete, Func fonction) const{  
        for(int id_road : rn.cities.at(arrete).roads){
            RoadNetwork::Road road = rn.roads.at(id_road);
            fonction(WeightedDirectedEdge<double>(road.cities.first,road.cities.second,coutCalcul(road)));   
        }
    };
    
    //applique une fonction à tous les sommets
    template<typename Func>
    void forEachVertex(Func fonction) const{
        for(int id_city = 0; id_city < rn.cities.size(); ++id_city){
            fonction(id_city);
        }
    }
};



#endif /* ROADDIGRAPHWRAPPER_H */
