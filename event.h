// Archivo: event.cc
// interfaz de la clase 'Event'
// R. Marcelin J. (2/08/99)

#if !defined(__EVENT_)
#define __EVENT_

class Event
{  public:
      Event();
      Event(char _name, float _time, int _target, int _source);  //
      ~Event();                          //
      char  getName();                   //
      float getTime();                   //
      int   getSource();                 //
      int   getTarget();                 //

   protected:
      char  name;                        // nombre
      float time;                        // estampilla de tiempo
      int   target;                      // destino
      int   source;                      // origen
};

#endif
