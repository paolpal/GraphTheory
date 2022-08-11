#include <iostream>
#include <limits>
using namespace std;

#include "../utility/comparable.h"
#include "../utility/heap.h"
#include "../utility/dijkstraHeap.h"
#include "../utility/graph.h"

#define N 6

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



int main(int argc, char const *argv[]) {
  Graph<char,int> G(N);

  dNode* nodes[N];
  bool extracted[N];

  DijkstraHeap<dNode> Q(N);

  G.addArc(0,1,8);
  G.addArc(0,2,5);
  G.addArc(1,3,9);
  G.addArc(1,4,4);
  G.addArc(2,1,1);
  G.addArc(2,4,7);
  G.addArc(3,5,5);
  G.addArc(4,3,4);
  G.addArc(4,5,3);

  nodes[0] = new dNode(0,0,0);
  Q.insert(*nodes[0]);
  for(int i=1; i<N; i++){
    extracted[i] = false;
    nodes[i] = new dNode(i,INT_MAX,-1);
    Q.insert(*nodes[i]);
  }

  dNode n;
  int j;
  for(int i=0; i<N; i++){
    n = Q.extract();
    extracted[n.nodeNumber] = true;
    cout << n << endl;
    Graph<char,int>::Node<int>* l = G.getList(n.nodeNumber);
    while(l!=NULL){
      j = l->nodeNumber;
      if(!extracted[j]){
        Q.extract(*nodes[j]);
        if(nodes[j]->dist > n.dist + l->arcLabel){
          nodes[j]->dist = n.dist + l->arcLabel;
          nodes[j]->pred = n.nodeNumber;
        }
        Q.insert(*nodes[j]);
      }
      l=l->next;
    }
  }

  return 0;
}
