#ifndef _GRAPH_H
#define _GRAPH_H

template<class NodeType, class ArcType = double>
class Graph{

public:
  template<class _ArcType = ArcType>
  struct Node{
    int nodeNumber;
    _ArcType arcLabel;

    Node<>* next;

    Node<>(int n, _ArcType l):nodeNumber(n),arcLabel(l),next(NULL){}
  };

private:
  int nodes;

  Node<>** graph;
  NodeType* labels;

  bool* mark;

  void nodeVisit(int i){
    mark[i]=1;

    Node<>* g;
    int j;
    for(g=graph[i]; g!=NULL; g=g->next){
      j = g->nodeNumber;
      if(!mark[j]) nodeVisit(j);
    }
  }

  void insert(Node<>*& l, int end, ArcType price){
    if(l==NULL){
      l = new Node<>(end,price);
      return;
    }
    if(end<l->nodeNumber){
      Node<>* tmp = new Node<>(end,price);
      tmp->next = l;
      l = tmp;
      return;
    }
    insert(l->next, end, price);
  }

public:

  Graph(int nodes){
    this->nodes = nodes;
    graph = new Node<>* [nodes];
    for(int i=0; i<nodes; i++) graph[i] = NULL;
    labels = new NodeType[nodes];
    mark = new bool[nodes];
  }

  int getNodes(){
    return nodes;
  }

  void addArc(int start, int end, ArcType price = 0){
    Node<>* tmp = new Node<>(end, price);
    //tmp->nodeNumber = end;
    //tmp->arcLabel = price;
    tmp->next = graph[start];
    graph[start] = tmp;
    //insert(graph[start], end, price);
  }

  void addNodeLabel(int node, NodeType label){
    labels[node] = label;
  }

  Node<>* getList(int listIndex){
    return graph[listIndex];
  }

  void depthVisit(){
    for (int i=0; i<nodes; i++) mark[i]=false;
    for (int i=0; i<nodes; i++) if(!mark[i]) nodeVisit(i);
  }
};

#endif
