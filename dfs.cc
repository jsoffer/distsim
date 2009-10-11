#include "simulation.h"

#include <iostream>

enum message { DESCUBRE = 'A', REGRESA = 'B', AVISO = 'C' };

class DFS;
class Message;

class Message: public Event
{  private: 
      friend class DFS;

   public:
      // constructor nulo
      Message()
      {};

      // constructor inicializado: nombre, tiempo, destino, origen
      Message(char n, float t, int d, int o): Event(n, t, d, o)
      {};

      // destructor
      ~Message()
      {};
};

class DFS: public Model
{  private:
      int visitado;
      int padre;

      LinkList<int> sin_visitar;

   public:
      virtual void init()
      {  int i, *n;
      
         visitado = 0;
         padre    = me;
         while (n = neighbors->next())
	    sin_visitar.inqueue(i = *n);
      };

      void send(char msj, int dst)
      {  Event *e;

         e = new Message(msj, clock+1.0, dst, me);
         transmit(e);
      }

      virtual void receive(Event *e)
      {  Message *te;

         atiende((Message *) e);
      };


      void continua_exploracion()
      {  int *h,l;

         if (!sin_visitar.isEmpty())
	 {  l = sin_visitar.dequeue();
            send(DESCUBRE, l);
         }
         else
         {  if (padre != me) 
               send(REGRESA, padre);
         };
      };
       
      void atiende(Message *e)
      {  int j = e->getSource();
         
         switch(e->getName())
	 {  case DESCUBRE:
	         std::cout << me << "@" << clock << " DESCUBRE from " << j << "\n";
                 sin_visitar.remove(j);
                 if (!visitado)
                 {  visitado = 1;
                    padre = j;
                    while (int *k = neighbors->next()) // sin_visitar NO!
                    {  if (padre != *k)  
                          send(AVISO, *k);
                    };
                    continua_exploracion();
                 };
                 break;
	    case REGRESA:
	         std::cout << me << "@" << clock << " REGRESA from " << j << "\n";
                 continua_exploracion();
                 break; 
            case AVISO: 
	         std::cout << me << "@" << clock << " AVISO from " << j << "\n";
                 sin_visitar.remove(j);
                 break;
         };
      };
};

main(int argc, char **argv)
{  
   Simulator *myEngine = new Simulator(500.0);
   Graph myNetwork(argv[1]);

   std::cout << "tamano de la red" << myNetwork.getSize() << "\n";
   Simulation myExperiment = Simulation(myNetwork, myEngine);
   for (int i = 1; i <= myNetwork.getSize(); i++)
   {  DFS *newmodel = new DFS();
      myExperiment.setModel(newmodel, i);
   }

   Message *e1 = new Message(DESCUBRE,0.0,1,1);
   myExperiment.init(e1);
   std::cout << "experimento inicializado\n";
   myExperiment.run();
}
