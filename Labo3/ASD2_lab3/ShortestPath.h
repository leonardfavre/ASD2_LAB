/* 
 * File:   ShortestPath.h
 * Author: Olivier Cuisenaire
 * Modified by: Leonard Favre, Guillaume Schranz, Matthieu Girard
 * Created on 5. novembre 2014, 10:16
 */

#ifndef ASD2_ShortestPath_h
#define ASD2_ShortestPath_h

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <functional>
#include <list>
#include <iostream>
#include <cstdlib>

// Classe parente de toutes les classes de plus court chemin.
// Defini les membres edgeTo et distanceTo commun à toutes ces
// classes, ainsi que les methodes DistanceTo, EdgeTo et PathTo
// qui permettent de les interroger.
//
// Le calcul des plus courts chemins est fait dans les constructeurs
// des classes derivees.

template<typename GraphType>   // Type du graphe pondere oriente a traiter
							   // GraphType doit se comporter comme un
							   // EdgeWeightedDiGraph et definir le
							   // type GraphType::Edge
class ShortestPath {
public:
	// Type des arcs. Normalement ASD2::DirectedEdge<double>
	typedef typename GraphType::Edge Edge;
	
	// Type des poids. Normalement double ou int.
	typedef typename Edge::WeightType Weight;

	// Listes d'arcs et de poids
	typedef std::vector<Edge> Edges;
	typedef std::vector<Weight> Weights;

	// Renvoie la distance du chemin le plus court du sommet source a v
	Weight DistanceTo(int v) {
		return distanceTo.at(v);
	}
	
	// Renvoie le dernier arc u->v du chemin le plus court du sommet source a v
	Edge EdgeTo(int v) {
		return edgeTo.at(v);
	}
	
	// Renvoie la liste ordonnee des arcs constituant un chemin le plus court du
	// sommet source à v.
	Edges PathTo(int v){
            //vecteur a retourner
            Edges listeOrdonnee;

            Edge edge = edgeTo.at(v);

            while(edge.From() != edge.To()){
                listeOrdonnee.push_back(edge);
                edge = edgeTo.at(edge.From());
            }

            std::reverse(listeOrdonnee.begin(), listeOrdonnee.end()); 

            return listeOrdonnee;
          }

protected:
	Edges edgeTo;
	Weights distanceTo;
};

// Classe a mettre en oeuvre au labo 3. S'inspirer de BellmaFordSP pour l'API

template<typename GraphType>
class DijkstraSP : public ShortestPath<GraphType> {
public:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;

        // Retourne le chemin le plus court à chaque sommet du graphe, depuis le sommet v
        // Utilise l'algorithme du cours, avec une simple liste pour contenir les sommets
	DijkstraSP(const GraphType& g, int v)  {
  /* A ETE IMPLEMENTE */
            std::list<int> q;
                        
            int u = v; // Pour une meilleure lisibilité vis-à-vis du cours
            
            this->distanceTo.resize(g.V());
            this->edgeTo.resize(g.V());
            this->distanceTo[u] = 0;
            
            g.forEachVertex([&](int v) {
                if (v != u) {
                    this->distanceTo[v] = std::numeric_limits<Weight>::max();
                }
                q.push_back(v);
            });
           
            while (!q.empty()) {
                int v = closestVertex(this->distanceTo, q);
                
                q.remove_if([&](int x) { return x == v; }); // On retire le sommet v de la liste
                
                g.forEachAdjacentEdge(v, [&](const Edge& e) {
                    auto distThruE = this->distanceTo[v] + e.Weight();
                    auto w = e.To();
                    if (distThruE < this->distanceTo[w]) {
                        this->distanceTo[w] = distThruE;
                        this->edgeTo[w] = e;
                    }
                });
            }
 }
        
private:
    // méthode qui retourne le sommet de Q qui le plus proche
    // v = min(distTo[v])
    int closestVertex(std::vector<Weight> const& distTo, std::list<int> q ) {
        auto distMin = std::numeric_limits<Weight>::max();
        int v = q.front();

        for (int i : q) {
            if (distTo[i] < distMin) {
                distMin = distTo[i];
                v = i;
            }
        }
        return v;
    }
};

// Algorithme de BellmanFord.

template<typename GraphType> // Type du graphe pondere oriente a traiter
							 // GraphType doit se comporter comme un
							 // EdgeWeightedDiGraph et definir forEachEdge(Func),
							 // ainsi que le type GraphType::Edge. Ce dernier doit
							 // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
							 // To() et Weight()

class BellmanFordSP : public ShortestPath<GraphType> {

private:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;
	
	// Relachement de l'arc e
	void relax(const Edge& e) {
		int v = e.From(), w = e.To();
		Weight distThruE = this->distanceTo[v]+e.Weight();
		
		if(this->distanceTo[w] > distThruE) {
			this->distanceTo[w] = distThruE;
			this->edgeTo[w] = e;
		}
	}
	
public:
	
	// Constructeur a partir du graphe g et du sommet v a la source
	// des plus courts chemins
	BellmanFordSP(const GraphType& g, int v) {
		
		this->edgeTo.resize(g.V());
		this->distanceTo.assign(g.V(),std::numeric_limits<Weight>::max());

		this->edgeTo[v] = Edge(v,v,0);
		this->distanceTo[v] = 0;
		
		for(int i=0;i<g.V();++i)
			g.forEachEdge([this](const Edge& e){
				this->relax(e);
			});
	}
};


/* Fera l'objet d'un exercice de programmation
// Algorithme de BellmanFord avec queue simple reprenant les sommets ayant
// ete modifies par la derniere iteration.
template<typename GraphType> // Type du graphe pondere oriente a traiter
							 // GraphType doit se comporter comme un
							 // EdgeWeightedDiGraph et definir forEachAdjacentEdge(int,Func),
							 // ainsi que le type GraphType::Edge. Ce dernier doit
							 // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
							 // To() et Weight()

class BellmanFordQueueSP : public ShortestPath<GraphType> {

private:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;
	
public:
	BellmanFordQueueSP(const GraphType& g, int v) {
		
	}
};
*/

#endif
