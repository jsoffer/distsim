// Archivo: model.cc
// implementacion de la clase 'Model'
// R. Marcelin J. (02/08/99)
// esta es una version modificada que extiende la definicion de la clase
// MODELO, para permitir la concatenacion de automatas (29/10/01).


#include "event.h"
#include "model.h"
#include "process.h"
#include <iostream.h>

//@ Model(): constructor
//------------------------------------------------------------------
Model::Model()
{  clock = 0;                                                      }


//@ ~Model(): destructor
//------------------------------------------------------------------
Model::~Model()
{                                                                  }


//@ init(): 
//------------------------------------------------------------------
void Model::init()
{                                                                  }

//@ init(): 
//------------------------------------------------------------------
void Model::init(int pid)
{                                                                  }


//@ transmit(): transmite evento
//------------------------------------------------------------------
void Model::transmit(Event *e)
{  myProcess->transmit(e);                                         }


//@ transmitAll(): 
//------------------------------------------------------------------
void Model::transmitAll(Event *e)
{  myProcess->transmitAll(e);                                      }


//@ receive(): recibe evento
//------------------------------------------------------------------
void Model::receive(Event *e) 
{                                                                  }









