#ifndef _GRAPH_H
#define _GRAPH_H

template<class ArcType>
struct Node{
  int nodeNumber;
  ArcType arcLabel;

  Node* next;

  Node(int n, ArcType l):nodeNumber(n),arcLabel(l),next(NULL){}
};

template<class NodeType, class ArcType = double>
class Graph{

private:
  int nodes;

  Node<ArcType>** graph;
  NodeType* labels;

  bool* mark;

  void nodeVisit(int i){
    mark[i]=1;

    Node<ArcType>* g;
    int j;
    for(g=graph[i]; g!=NULL; g=g->next){
      j = g->nodeNumber;
      if(!mark[j]) nodeVisit(j);
    }
  }

  void insert(Node<ArcType>*& l, int end, ArcType price){
    if(l==NULL){
      l = new Node<ArcType>(end,price);
      return;
    }
    if(end<l->nodeNumber){
      Node<ArcType>* tmp = new Node<ArcType>(end,price);
      tmp->next = l;
      l = tmp;
      return;
    }
    insert(l->next, end, price);
  }

public:

  Graph(int nodes){
    this->nodes = nodes;
    graph = new Node<ArcType>* [nodes];
    for(int i=0; i<nodes; i++) graph[i] = NULL;
    labels = new NodeType[nodes];
    mark = new bool[nodes];
  }

  int getNodes(){
    return nodes;
  }

  void addArc(int start, int end, ArcType price = 0){
    Node<ArcType>* tmp = new Node<ArcType>(end, price);
    //tmp->nodeNumber = end;
    //tmp->arcLabel = price;
    tmp->next = graph[start];
    graph[start] = tmp;
    //insert(graph[start], end, price);
  }

  void addNodeLabel(int node, NodeType label){
    labels[node] = label;
  }

  Node<ArcType>* getList(int listIndex){
    return graph[listIndex];
  }

  void depthVisit(){
    for (int i=0; i<nodes; i++) mark[i]=false;
    for (int i=0; i<nodes; i++) if(!mark[i]) nodeVisit(i);
  }
};

#endif
