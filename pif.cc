#include "simulation.h"

#include <iostream>

enum estado { DUERME    = 'a',
              CONSTRUYE = 'b',
              VIGILA    = 'c'};

enum nombre { EXPLORA   = 'A',
              REMUEVE   = 'B',
              REMONTA   = 'C'};

class PIF;
class Mensaje;

class Mensaje: public Event
{  private:
      friend class PIF;

   public:
      // constructor nulo
      Mensaje()
      {};

      // constructor inicializado: nombre, tiempo, destino, origen
      Mensaje(char n, float t, int d, int o):
      Event(n, t, d, o)
      {};

      // destructor
      ~Mensaje()
      {};
};

class PIF: public Model
{  private:
      int situacion;
      int padre;
      int cuenta;

      LinkList<int> hijos;
      LinkList<int> sin_visitar;

   public:
      virtual void init()
      {  int i, *n;
      
         situacion = DUERME;
         padre     = me;
         cuenta= -1;

         while (n  = neighbors->next())
	    sin_visitar.inqueue(i = *n);
      };

      void send(char msj, int dst)
      {  Event *e;

         e = new Mensaje(msj, clock+1.0, dst, me);
         transmit(e);
      }

      virtual void receive(Event *e)
      {  
         atiende((Mensaje *) e);
      };

      void propaga(LinkList<int> *lista)
      {

         cuenta=0;
         if (!lista->isEmpty())
            while (int *k = lista->next())
            {  send(EXPLORA, *k);
               cuenta++;
            }
      }

   
      void atiende(Mensaje *e)
      {  int j = e->source;
         
         switch(e->name)
         {  case EXPLORA:
                 std::cout << me << "@" << clock << " EXPLORA from " << j << "\n";
                 switch(situacion)
                 {  case DUERME:
                         situacion=CONSTRUYE;
                         padre=j;
                         sin_visitar.remove(j);
                         propaga(&sin_visitar);
                         break;
                    case CONSTRUYE:
                         cuenta--;
                         if (cuenta==0)
                         {  situacion=VIGILA;
                            if (padre!=me)
                               send(EXPLORA, padre);
                         };   
                         break;
                 };
                 break;
         };
      };
};

main(int argc, char **argv)
{  
   Simulator *myEngine = new Simulator(25.0);
   Graph myNetwork(argv[1]);

   std::cout << "tamano de la red" << myNetwork.getSize() << "\n";
   Simulation myExperiment = Simulation(myNetwork, myEngine);
   for (int i = 1; i <= myNetwork.getSize(); i++)
   {  PIF *newmodel = new PIF();
      myExperiment.setModel(newmodel, i);
   }

   Mensaje *e1 = new Mensaje(EXPLORA, 0.0, 1, 1);
   myExperiment.init(e1);
   std::cout << "experimento inicializado\n";
   myExperiment.run();
}
