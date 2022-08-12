#include "comparable.h"
#include "heap.h"
#include "dijkstraHeap.h"
#include "graph.h"

#include <iostream>
using namespace std;
#include <limits>

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

// pred - predecessore deve essere int
// aggiungi uncampo label

template <class L = int, class T = int>
struct dNode : sComparable<T>{
  T dist;
  L label;
  int pred;
  int nodeNumber;
  int heapIndex;

  dNode():sComparable<T>(dist){}

  dNode(int n, T d, int p):sComparable<T>(dist){
    dist = d;
    pred = p;
    nodeNumber = n;
  }

  dNode& operator=(const dNode<L,T>& s){
    dist = s.dist;
    nodeNumber = s.nodeNumber;
    pred = s.pred;
    return *this;
  }

  bool operator==(dNode<L,T>& c){
    return nodeNumber==c.nodeNumber;
  }
};

template <class L, class T>
ostream& operator<<(ostream& os, const dNode<L,T>& n){
  os << "Nodo: " << n.nodeNumber << " Distanza: " << n.dist << " Predecessore: " << n.pred << " Label: " << n.label;
  return os;
}

template <class L = int, class T = int>
class Dijkstra{
  Graph<L,T> *G;
  bool *inS;
  DijkstraHeap< dNode<L,T> > *Q;
  int nodes;

public:
  Dijkstra(Graph<L,T> &G){
    this->G = &G;
    nodes = G.getNodes();

    Q = new DijkstraHeap< dNode<L,T> >(nodes);
    inS = new bool[nodes];

    for(int i=0; i<nodes; i++){
      inS[i] = false;
      //Q->insert(dNode<L,T>(i,INT_MAX,-1));
      Q->insert(dNode<L,T>(i,numeric_limits<T>::max(),-1));
    }
  }

  void start(int node){
    Q->extract(node);
    Q->insert(dNode<L,T>(node,0,0));

    dNode<L,T> nodo1, nodo2;
    int j;

    Node<T> *l;
    for(int i=0; i<nodes; i++){
      nodo1 = Q->extract();
      inS[nodo1.nodeNumber] = true;
      cout << nodo1 << endl;
      //Graph<L,T>::Node* l = G->getList(nodo1.nodeNumber);
      l = G->getList(nodo1.nodeNumber);
      while(l!=NULL){
        j = l->nodeNumber;
        if(!inS[j]){
          nodo2 = Q->extract(j);
          if(nodo2.dist > nodo1.dist + l->arcLabel){
            nodo2.dist = nodo1.dist + l->arcLabel;
            nodo2.pred = nodo1.nodeNumber;
          }
          Q->insert(nodo2);
        }
        l=l->next;
      }
    }
  }

};

#endif
