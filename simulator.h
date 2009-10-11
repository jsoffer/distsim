// Archivo: simulator.h 
// interfaz de la clase 'Simulator'
// R. Marcelin J. (02/08/99)

#if !defined(__SIMULATOR_)
#define __SIMULATOR_

#include "event.h"
#include "avltree.cc"

class Simulator
{  
   public:
      Simulator(float d);                //
      ~Simulator();                      //  
      void insertEvent(Event *e);        // 
      Event *dequeueEvent();             // 
      int isOn();                        //

   private:
      float duration;
      float clock;                       //
      AVLTree<Event *> agenda;           //
};

#endif











