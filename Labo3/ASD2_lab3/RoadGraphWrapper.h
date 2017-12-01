/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoadGraphWrapper.h
 * Author: guill
 *
 * Created on 30. novembre 2017, 13:49
 */

#ifndef ROADGRAPHWRAPPER_H
#define ROADGRAPHWRAPPER_H

template <typename Fonction>
class RoadGraphWrapper {
private:
    RoadNetwork rn; 
    Fonction coutCalcul;
    
public:
    typedef WeightedEdge<double> Edge;
    
    // Constructeur du wrapper
    RoadGraphWrapper(const RoadNetwork& rn, Fonction fonction): rn(rn), coutCalcul(fonction){}
    
    // nombre de sommet du graph
    int V() const {
        return int(rn.cities.size());
    }
    
    //applique une fonction à toutes les aretes du graph
    template<typename Func>
    void forEachEdge(Func fonction) const{
        for(RoadNetwork::Road road : rn.roads){
            Edge temp(road.cities.first,road.cities.second,coutCalcul(road));
            fonction(temp);
        }
    }
};


#endif /* ROADGRAPHWRAPPER_H */

