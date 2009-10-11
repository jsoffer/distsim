// Archivo: process.cc
// implementacion de la clase 'Process'
// R. Marcelin J. (02/08/99)
// esta es una version modificada que extiende la definicion de la clase
// MODELO, para permitir la concatenacion de automatas (29/10/01).


#include "process.h"
#include <iostream.h>


//@ Process(): constructor
//------------------------------------------------------------------
Process::Process(LinkList<int> &_tx, Simulator *eng, int _id):
txSet(_tx), myEngine(eng), id(_id)
{                                                                  }


//@ ~Process(): destructor
//------------------------------------------------------------------
Process::~Process()
{                                                                  }


//@ setModel(): 
//------------------------------------------------------------------
void Process::setModel(Model *model)
{  int pid;
   Model **m1, *m2;

   myModel = model;
   myModel->myProcess = this;
   myModel->me = id;
   myModel->neighbors = &txSet;
   myModel->init();
   pid = 1;
   while (m1=(myModel->partners.next()))
   {  m2=*m1;
      m2->myProcess = this;
      m2->me = id;
      m2->neighbors = &txSet;
      m2->init(pid++);
      m2->partners.insert(model, 1);
   };
}


//@ transmit():
//------------------------------------------------------------------
void Process::transmit(Event *e)
{  myEngine->insertEvent(e);                                       }


//@ sendAll():
//------------------------------------------------------------------
void Process::transmitAll(Event *e)
{
//     int *to;
//     Event *ecopy;

//     while (to = getTxNeighbor())  
//     {  ecopy = new Event(e->getName(), e->getTime()+1, *to, e->getSource());
//        myEngine->insertEvent(ecopy);
//     };                                       
}


//@ receive():
//------------------------------------------------------------------
void Process::receive(Event *e)
{  Model **m1, *m2;

   myModel->clock = e->getTime();

   while (m1=(myModel->partners.next()))
   {  m2=*m1;
      m2->clock = myModel->clock;
   };

   myModel->receive(e);                                            
}


//@ addTxNeighbor():
//------------------------------------------------------------------
void Process::addTxNeighbor(int _id)
{  txSet.insert(_id);                                              }


//@ addRxNeighbor():
//------------------------------------------------------------------
void Process::addRxNeighbor(int _id)
{  rxSet.insert(_id);                                              }


//@ getTxNeighbor():
//------------------------------------------------------------------
int *Process::getTxNeighbor()
{  return txSet.next();                                            }


//@ getRxNeighbor():
//------------------------------------------------------------------
int *Process::getRxNeighbor()
{  return rxSet.next();                                            }











