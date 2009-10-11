// Archivo: simulator.cc 
// implementacion de la clase 'Simulator'
// R. Marcelin J. (02/08/98)

#include "simulator.h"


//@ Simulator(): constructor
//------------------------------------------------------------------
Simulator::Simulator(float d)
{  clock = 0.0;                                                    
   duration = d;
}


//@ ~Simulator(): destructor
//------------------------------------------------------------------
Simulator::~Simulator()
{                                                                  }


//@ insertEvent():
//------------------------------------------------------------------
void Simulator::insertEvent(Event *e)
{  
   float key = e->getTime();
   agenda.insert(e, key);                                               
}


//@ dequeueEvent():
//------------------------------------------------------------------
Event *Simulator::dequeueEvent()
{  
   Event *e; 
   e = agenda.minval();
   clock = e->getTime();
   return e; 
}


//@ isOn():
//------------------------------------------------------------------
int Simulator::isOn()
{  return (!agenda.isEmpty())&&(clock <= duration);                }












