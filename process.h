// Archivo: process.h
// interfaz de la clase 'Process'
// R. Marcelin J. (02/08/99)
// esta es una version modificada que extiende la definicion de la clase
// MODELO, para permitir la concatenacion de automatas (29/10/01).


#if !defined(__PROCESS_)
#define __PROCESS_

#include "model.h"
#include "event.h"
#include "simulator.h"
#include "linklist.cc"
//#include "intset.h"

class Process
{  
   public:
      Process(LinkList<int> &_tx, Simulator *engine, int _id);
      ~Process();                        //
      void setModel(Model *model);
      void transmit(Event *e);		 // 
      void transmitAll(Event *e);        //
      void receive(Event *e);            //
      void addTxNeighbor(int _id);       //
      void addRxNeighbor(int _id);       //
      int *getTxNeighbor();              // devuelve  ap. al item, o nulo
      int *getRxNeighbor();              // devuelve  ap. al item, o nulo
      friend class Model;

   private:
      int id;                            //
      Model *myModel;                    // 
      Simulator *myEngine;               //
      LinkList<int> txSet;               //
      LinkList<int> rxSet;               //
};

#endif
