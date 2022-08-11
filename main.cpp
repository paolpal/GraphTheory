#include <iostream>
#include <limits>
using namespace std;

#include "utility/comparable.h"
#include "utility/heap.h"
#include "utility/dijkstraHeap.h"
#include "utility/dijkstra.h"
#include "utility/graph.h"

#define N 6

int main(int argc, char const *argv[]) {

  int n, r;
  int n1, n2, c;

  cin >> n >> r;

  Graph<char,int> G(n);

  for(int i=0; i<r; i++){
    cin >> n1 >> n2 >> c;
    G.addArc(n1,n2,c);
  }

  Dijkstra D1(G);
  //Dijkstra D2(G);

  D1.start(5);
  //D2.start(57);


  return 0;
}
