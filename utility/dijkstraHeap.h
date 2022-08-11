#include "heap.h"

#ifndef _DJK_HEAP_H
#define _DJK_HEAP_H

template <class T>
class DijkstraHeap: public MinHeap<T>{
protected:
  using MinHeap<T>::h;
  using MinHeap<T>::last;
  using MinHeap<T>::exchange;
  int *indexes;

  void up(int i){
    if(i>0){
      int f = (i-1)/2;
      if(h[i]<h[f]){
        exchange(i,f);
        indexes[h[i].nodeNumber] = i;
        indexes[h[f].nodeNumber] = f;
        up(f);
      }
    }
  }

  void down(int i){
    int s = 2*i+1;
    if(s == last){
      if(h[s] < h[i]){
        exchange(i,s);
        indexes[h[i].nodeNumber] = i;
        indexes[h[s].nodeNumber] = s;
      }
    }
    else if(s < last){
      if(h[s] > h[s+1]) s++;
      if(h[s] < h[i]){
        exchange(i,s);
        indexes[h[i].nodeNumber] = i;
        indexes[h[s].nodeNumber] = s;
        down(s);
      }
    }
  }

public:

  DijkstraHeap(int n):MinHeap<T>(n){
    indexes = new int[n];
    for(int i=0; i<n; i++) indexes[i]=-1;
  }

  ~DijkstraHeap(){
    delete [] indexes;
  }

  void insert(T x){
    last++;
    h[last] = x;
    indexes[x.nodeNumber]=last;
    up(last);
  }

  T extract(){
    T r = h[0];
    indexes[h[0].nodeNumber]=-1;
    h[0] = h[last];
    indexes[h[0].nodeNumber]=0;
    last--;
    down(0);
    return r;
  }

  bool extract(T& elem){
    bool r = false;
    int i = indexes[elem.nodeNumber];
    if(i!=-1) r = true;
    if(r){
      elem = h[i];
      indexes[elem.nodeNumber]=-1;
      h[i] = h[last];
      indexes[h[i].nodeNumber]=i;
      last--;
      down(i);
    }
    return r;
  }

  T extract(int nodeNumber){
    T elem;
    //bool r = false;
    int i = indexes[nodeNumber];
    //if(i!=-1) r = true;
    if(i!=-1){
      elem = h[i];
      indexes[h[i].nodeNumber]=-1;
      h[i] = h[last];
      indexes[h[i].nodeNumber]=i;
      last--;
      down(i);
    }
    return elem;
  }
};

#endif
