#include "comparable.h"
#include "heap.h"
#include "dijkstraHeap.h"
#include "graph.h"

#include <iostream>
using namespace std;
#include <limits>

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

struct dNode : sComparable<int>{
  int dist;
  int pred;
  int nodeNumber;
  int heapIndex;

  dNode():sComparable<int>(dist){}

  dNode(int n, int d, int p):sComparable<int>(dist){
    dist = d;
    pred = p;
    nodeNumber = n;
  }

  dNode& operator=(const dNode& s){
    dist = s.dist;
    nodeNumber = s.nodeNumber;
    pred = s.pred;
    return *this;
  }

  bool operator==(dNode& c){
    return nodeNumber==c.nodeNumber;
  }
};

ostream& operator<<(ostream& os, const dNode& n){
  os << "Nodo: " << n.nodeNumber << " Distanza: " << n.dist << " Predecessore: " << n.pred;
  return os;
}


class Dijkstra{
  Graph<char,int> *G;
  bool *inS;
  DijkstraHeap<dNode> *Q;
  int nodes;

public:
  Dijkstra(Graph<char,int> &G){
    this->G = &G;
    nodes = G.getNodes();

    Q = new DijkstraHeap<dNode>(nodes);
    inS = new bool[nodes];

    for(int i=0; i<nodes; i++){
      inS[i] = false;
      Q->insert(dNode(i,INT_MAX,-1));
    }
  }

  void start(int node){
    Q->extract(node);
    Q->insert(dNode(node,0,0));

    dNode nodo1, nodo2;
    int j;
    for(int i=0; i<nodes; i++){
      nodo1 = Q->extract();
      inS[nodo1.nodeNumber] = true;
      cout << nodo1 << endl;
      Graph<char,int>::Node<int>* l = G->getList(nodo1.nodeNumber);
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
