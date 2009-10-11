// Archivo: event.cc
// implementacion de la clase 'Event'
// R. Marcelin J. (2/08/99)

#include "event.h"

//@ Event(): constructor
//------------------------------------------------------------------
Event::Event()
{                                                                  }


//@ Event(): constructor
//------------------------------------------------------------------
Event::Event(char _name, float _time, int _target, int _source)
{  name   = _name;
   time   = _time;
   target = _target;
   source = _source;
}


//@ ~Event(): destructor
//------------------------------------------------------------------
Event::~Event(void)
{                                                                  }


//@ getName(): 
//------------------------------------------------------------------
char Event::getName(void)
{  return name;                                                    }


//@ getTime()
//------------------------------------------------------------------
float Event::getTime(void)
{  return time;                                                    }

//@ getSource()
//------------------------------------------------------------------
int Event::getSource(void)
{  return source;                                                  }


//@ getTarget()
//------------------------------------------------------------------
int Event::getTarget(void)
{  return target;                                                  }

