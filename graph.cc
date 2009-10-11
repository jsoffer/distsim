// Archivo: graph.cc
// implementacion de la clase 'Graph'
// R. Marcelin J. (02/08/99)

#include "graph.h"

#include <iostream>

//@ Graph(): constructor 
//------------------------------------------------------------------
Graph::Graph(char *file)              
{  char c;
   int temp;
   int vertice;
   int weight;
   LinkList<int> *v;
   ifstream ins(file);

   if (!ins)
   {  std::cerr << "No pude abrir el archivo\n";
      exit(1);
   };

   for (size = 0; !ins.eof(); size++)
   {  v = new LinkList<int>();
      while ((ins.get(c))&&(c!=NEWL))
      {  ins.unget();
         vertice = 0;
         while ((ins.get(c))&&(c!=' ')&&(c!=','))
	 {  temp = c - '0';
            vertice=10*vertice+temp;
         };

         if (c==',')
	 {  weight = 0;
            while ((ins.get(c))&&(c!=' ')&&(c!=','))
	    {  temp = c - '0';
               weight=10*weight+temp;
            };
         };
            
         while ((ins.get(c))&&(c==' '));
         ins.unget();
         if (weight)
            v->insert(vertice, weight);
         else
            v->insert(vertice);
      };
      g.insert(v, size + 1);
   };
   ins.close();
}

//@ Graph(): destructor 
//------------------------------------------------------------------
Graph::~Graph()
{                                                                  }

//@ getSize(): devuelve num. de vertices
//------------------------------------------------------------------
int Graph::getSize()
{  return size;                                                    }

//@ getRow(): devuelve la lista de vecinos del vertice 'id' 
//------------------------------------------------------------------
LinkList<int> *Graph::getRow(int id)
{   return *(g.find(id));                                          }








