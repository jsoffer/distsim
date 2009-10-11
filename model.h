// Archivo: model.h
// intefaz de la clase 'Model'
// R. Marcelin J. (02/08/99)
// esta es una version modificada que extiende la definicion de la clase
// MODELO, para permitir la concatenacion de automatas (29/10/01).

#if !defined(__MODEL_)
#define __MODEL_

#include "event.h"
#include "linklist.cc"
//#include "intset.h"

class Process; /* no puedo incluir process.h, dep. mutua */

class Model
{  
   public:
      Model();                           // constructor
      ~Model();                          // destructor
      virtual void init();
      virtual void init(int pid);
      void transmit(Event *e);           // envia evento
      void transmitAll(Event *e);
      virtual void receive(Event *e);    // recibe event
      friend class Process;

   protected:
      Process *myProcess;                // proceso a cargo
      int me;
      LinkList<int> *neighbors;
      LinkList<Model *> partners;       // esta es la modificacion
      float clock;
};

#endif

