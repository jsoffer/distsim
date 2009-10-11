#include "simulation.h"
#include <iostream.h>
class ALG;
class Message;

class Message: public Event
{  private: 
      friend class ALG;

   public:
      Message(char n, float t, int d, int o):
      Event(n, t, d, o)
      {};

      ~Message()
      {};
};

class ALG: public Model
{  private:
      int visitado;

   public:

      virtual void init()
      {  visitado = 0; 
      };

      void send(char msg, int dst)
      {  Event *e;

         e = new Message(msg, clock+1.0, dst, me);
         transmit(e);
      }



      virtual void receive(Event *e)
      { 
         if (!visitado)
	 {  cout << e->getTarget() << ":recibo " << clock << "\n";
            while (int *k  = neighbors->next())
            {   send('c', *k);
                cout << "envio a " << *k << "\n";
            };
            visitado = 1;
         }
         else
	    cout << e->getTarget() << ":termino " << clock << "\n";
      };
};


main(int argc, char **argv)
{  
   Simulator *myEngine = new Simulator(500.0);
   Graph myNetwork(argv[1]);

   Simulation myExperiment = Simulation(myNetwork, myEngine);
   for (int i = 1; i <= myNetwork.getSize(); i++)
   {  ALG *newmodel = new ALG();
      myExperiment.setModel(newmodel, i);
   }

   Event *e = new Event('c',1.0,1,1);
   myExperiment.init(e);
   myExperiment.run();
}



