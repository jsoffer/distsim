// Archivo: simulation.cc
// interfaz de la clase 'Simulation'
// R. Marcelin J. (02/08/98)

#if !defined(__SIMULATION_)
#define __SIMULATION_

#include "graph.h"
#include "model.h"
#include "event.h"
#include "process.h"
#include "simulator.h"
#include "avltree.cc"

class Simulation
{  
   public:
      Simulation(Graph graph, Simulator *engine);
      ~Simulation();                     //
      void setModel(Model *model, int id);
      void init(Event *e);               // 
      void run();                        //

   private:
      Graph net;                         //
      AVLTree<Process> table;            //  
      Simulator *myEngine;               //  
};

#endif
