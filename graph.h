// Archivo: graph.cc
// interface de la clase 'Graph'
// R. Marcelin J. (02/08/99)

#if !defined(__GRAPH_)
#define __GRAPH_

#include <fstream.h>
#include "linklist.cc"

const int NEWL = 10;

class Graph
{  
   public:
      Graph(char *file);		// constructor
      ~Graph();			        // destructor 
      int getSize();		        // devuelve num. vertices
      LinkList<int> *getRow(int id);    // devuelve un renglon de 'g'

   private:
      int size;			        // taman~o de la grafica
      LinkList<LinkList<int> *> g;      // 'matriz' de adyacencias
};

#endif
