//#include "comparable.h"

#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

template <class T>
class MinHeap {
protected:
  T* h;
  int last;
  void virtual up(int);
  void virtual down(int);
  void exchange(int i, int j){
    T k = h[i];
    h[i] = h[j];
    h[j] = k;
  }
public:
  MinHeap(int);
  ~MinHeap();
  void virtual insert(T);
  T virtual extract();
  bool virtual extract(T&);
};

template <class T>
MinHeap<T>::MinHeap(int n){
  h = new T[n];
  last = -1;
}

template <class T>
MinHeap<T>::~MinHeap(){
  delete [] h;
}

template <class T>
void MinHeap<T>::up(int i){
  if(i>0){
    int f = (i-1)/2;
    if(h[i]<h[f]){
      exchange(i,f);
      up(f);
    }
  }
}

template <class T>
void MinHeap<T>::insert(T x){
  last++;
  h[last] = x;
  up(last);
}

template <class T>
void MinHeap<T>::down(int i){
  int s = 2*i+1;
  if(s == last){
    if(h[s] < h[i]) exchange(i,s);
  }
  else if(s < last){
    if(h[s] > h[s+1]) s++;
    if(h[s] < h[i]){
      exchange(i,s);
      down(s);
    }
  }
}

template <class T>
T MinHeap<T>::extract(){
  T r = h[0];
  h[0] = h[last];
  last--;
  down(0);
  return r;
}

template <class T>
bool MinHeap<T>::extract(T& elem){
  bool r = false;
  int i = 0;
  while(i<=last){
    if(h[i]==elem){
      elem = h[i];
      r = true;
      break;
    }
    i++;
  }
  if(r){
    h[i] = h[last];
    last--;
    down(i);
  }
  return r;
}

#endif
