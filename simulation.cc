// Archivo: simulation.cc
// implementacion de la clase 'Simulation'
// R. Marcelin J. (02/08/98)

#include "simulation.h"

//@ Simulation(): constructor
//------------------------------------------------------------------
Simulation::Simulation(Graph graph, Simulator *engine):
net(graph)
{  int i, *r;
   Process *newproc;
   LinkList<int> *row;

   myEngine = engine;

   for (i = 1; i <= net.getSize(); i++)
   {  row = net.getRow(i);
      newproc = new Process(*row, engine, i);
      table.insert(*newproc, i);
   };

   for (i = 1; i <= net.getSize(); i++)
   {  row = net.getRow(i);
      while (r = row->next())
      {  newproc = table.find(*r);
         newproc->addRxNeighbor(i);
      }; 
   };
}


//@ ~Simulation(): destructor
//------------------------------------------------------------------
Simulation::~Simulation()
{                                                                  }


//@ setModel(): 
//------------------------------------------------------------------
void Simulation::setModel(Model *model, int id)
{
   Process *proc;

   proc = table.find(id);
   proc->setModel(model);                                                                  
}


//@ init(): 
//------------------------------------------------------------------
void Simulation::init(Event *e)
{  myEngine->insertEvent(e);                                       }


//@ run(): 
//------------------------------------------------------------------
void Simulation::run()
{  int t;
   Event *e;
   Process *nextproc;

   while(myEngine->isOn())
   {  e = myEngine->dequeueEvent();
      t = e->getTarget();
      nextproc = table.find(t);
      nextproc->receive(e);
   };  
}


