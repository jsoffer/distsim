// Archivo: linklist.cc
// implementacion de las clases parametrizadas 'LinkItem' y 'LinkList'
// R. Marcelin J. (21/06/99).
// (25/10/01) agregue los metodos "insertmarked()".

#if !defined(__LINKLIST_)
#define __LINKLIST_

//#include "trace.h"                    // para rastrear operaciones
//DEFINE_TRACE_MODULE(lnk, "lnk");

template <class T> class LinkItem;      // item de una lista ligada
template <class T> class LinkList;      // lista ligada
//class IntSet;

template <class T> class LinkItem      
{  
   public:
      LinkItem();                       // constructor por omision
      LinkItem(T &_info);               // constructor de tipos basicos
      LinkItem(T &_info, float _key);   // constructor de clases compuestas
      ~LinkItem();                      // destructor
      LinkItem<T> *getPos();            //
      LinkItem<T> *getPre();            //
      T &getInfo();                     //
      void setPos(LinkItem<T> *_pos);   //
      void setPre(LinkItem<T> *_pre);   //
      void setMark();                   // 
      void resetMark();                 //
      int isMarked();                   //  
      friend class LinkList<T>;         // acceso a los atrib. privados
//      friend class IntSet;

   protected:
      float key;                          // para establecer un orden
      T info;                           // campo de informacion
      int marked;                       // 
      LinkItem<T> *pos;                    // apunta al vecino posterior
      LinkItem<T> *pre;                    // apunta al vecino previo

};





template <class T> class LinkList       // eficiente para  ~cientos de items
{  
   public:
      LinkList();                       // constructor por omision
      ~LinkList();                      // destructor
      int getLength();                  // devuelve la long. de la lista
      int isEmpty();		        // verdadero si esta vacia
      void insert(LinkItem<T> *t);      // agrega en orden segun la llave
      void insert(T &_info, float _key);//
      void insert(T &_info);            //
      void insertmarked(T &_info, float _key);//
      void insertmarked(T &_info);      // 
      void remove(float _key);          // elimina al item que tiene la llave
      void inqueue(LinkItem<T> *t);     // agrega al final
      void inqueue(T &_info, float _key); // 
      void inqueue(T &_info);           // 
      T dequeue();                      // extrae al primero, usar c/isEmpty()
      T *find(float _key);              // busca un item por su llave
      T *next();                        // devuelve el sig. item sin visitar
                                        // o 0, si ya acabo.
      T *next(float &_key);             // tambien devuelve su llave de orden
                                        // como efecto lateral
   protected:
      LinkItem<T> *head;                // Estos son los pivotes de la
      LinkItem<T> *tail;                // lista.
      int length;
};





//@ LinkItem(): constructor por omision
//------------------------------------------------------------------
template<class T> LinkItem<T>::LinkItem()                        
{  key        = -1;              
   pos        =  0;
   pre        =  0;        
   marked     =  0;      
//   TRACE(lnk, -1, ("LinkItem constructor\n"));
}


//@ LinkItem(): constructor para tipos basicos
//------------------------------------------------------------------
template<class T> LinkItem<T>::LinkItem(T &_info)                
{  info       = _info;
   key        = _info; 
   pos        = 0;
   pre        = 0;        
   marked     = 0;      
//   TRACE(lnk, -1, ("LinkItem constructor\n"));
}


//@ LinkItem(): constructor para clases
//------------------------------------------------------------------
template<class T> LinkItem<T>::LinkItem(T &_info, float _key): info(_info)    
{  key        = _key;
   pos        = 0;
   pre        = 0;        
   marked     = 0;      
//   TRACE(lnk, -1, ("LinkItem constructor\n"));
}


//@ ~LinkItem(): destructor
//------------------------------------------------------------------
template<class T> LinkItem<T>::~LinkItem()                      
{  
//TRACE(lnk, -1, ("LinkItem destructor\n"));                      
}


//@ getPos():  
//------------------------------------------------------------------
template<class T> LinkItem<T> *LinkItem<T>::getPos()                  
{  return pos;                                                     }


//@ getPre():  
//------------------------------------------------------------------
template<class T> LinkItem<T> *LinkItem<T>::getPre()                  
{  return pre;                                                     }


//@ getInfo():  
//------------------------------------------------------------------
template<class T> T &LinkItem<T>::getInfo()                  
{  return info;                                                    }


//@ setPos():  
//------------------------------------------------------------------
template<class T> void LinkItem<T>::setPos(LinkItem<T> *_pos)                  
{  pos = _pos;                                                     }


//@ setPre():  
//------------------------------------------------------------------
template<class T> void LinkItem<T>::setPre(LinkItem<T> *_pre)                  
{  pre = _pre;                                                     }


//@ setMark():  
//------------------------------------------------------------------
template<class T> void LinkItem<T>::setMark()                  
{  marked = 1;                                                     }


//@ resetMark():  
//------------------------------------------------------------------
template<class T> void LinkItem<T>::resetMark()                  
{  marked = 0;                                                     }


//@ isMarked(): 
//------------------------------------------------------------------
template<class T> int LinkItem<T>::isMarked()                    
{  return marked;                                                  }





//@ LinkList(): constructor por omision
//------------------------------------------------------------------
template<class T> LinkList<T>::LinkList()
{  head = new LinkItem<T>(); 
   tail = new LinkItem<T>();
   head->pos = tail;        
   tail->pre = head;
   length = 0;
   
//   TRACE(lnk, -1, ("LinkList constructor\n"));
}


//@ ~LinkList(): destructor
//------------------------------------------------------------------
template<class T> LinkList<T>::~LinkList()
{  
// TRACE(lnk, -1, ("LinkList destructor\n"));                     
}


//@ getLength(): 
//------------------------------------------------------------------
template<class T> int LinkList<T>::getLength()
{  return length;                                                  }


//@ isEmpty():
//------------------------------------------------------------------
template<class T> int LinkList<T>::isEmpty()
{  return (head->pos == tail);                                     }


// @ insert(): agrega en orden segun la llave 't.key'
//------------------------------------------------------------------
template<class T> void LinkList<T>::insert(LinkItem<T> *t) 
{  LinkItem<T> *h1, *h2;

   h2 = head;

   h1 = h2->pos;
   while ((h1!=tail)&&(t->key >= h1->key))
   {  h2 = h1; h1 = h1->pos;
   };
   h2->pos = t; t->pre = h2; h1->pre = t; t->pos = h1;
   length++;
}


// @ insert();
//------------------------------------------------------------------
template<class T> void LinkList<T>::insert(T &_info, float _key) 
{  LinkItem<T> *h1, *h2, *t;

   t = new LinkItem<T>(_info, _key);
   insert(t);
}

//@ insert(): 
//------------------------------------------------------------------
template<class T> void LinkList<T>::insert(T &_info) 
{  LinkItem<T> *h1, *h2, *t;

   t = new LinkItem<T>(_info);
   insert(t);
}

// @ insertmarked():
//------------------------------------------------------------------
template<class T> void LinkList<T>::insertmarked(T &_info, float _key) 
{  LinkItem<T> *h1, *h2, *t;

   t = new LinkItem<T>(_info, _key);
   t->setMark();
   insert(t);
}

//@ insertmarked(): 
//------------------------------------------------------------------
template<class T> void LinkList<T>::insertmarked(T &_info) 
{  LinkItem<T> *h1, *h2, *t;

   t = new LinkItem<T>(_info);
   t->setMark();
   insert(t);
}



//@ remove(): elimina al item con la llave indicada
//------------------------------------------------------------------
template<class T> void LinkList<T>::remove(float _key) 
{  LinkItem<T> *h1, *h2, *h3;

   h2 = head;
   h1 = h2->pos;
   while ((h1!=tail)&&(h1->key!=_key))
   {  h2 = h1; h1 = h1->pos;
   };
   if (h1!=tail)
   {  h3 = h1;
      h1 = h1->pos;
      h2->pos = h1;
      h1->pre = h2;
      delete h3;
      length--;
   };
}


//@ inqueue(): agrega al final
//------------------------------------------------------------------
template<class T> void LinkList<T>::inqueue(LinkItem<T> *t) 
{  LinkItem<T> *h1, *h2;

   h1 = tail;
   h2 = h1->pre;
   h2->pos = t; t->pre = h2; h1->pre = t; t->pos = h1;
   length++;
}


//@ inqueue(): 
//------------------------------------------------------------------
template<class T> void LinkList<T>::inqueue(T &_info, float _key) 
{  LinkItem<T> *t;

   t = new LinkItem<T>(_info, _key);
   inqueue(t);
}


//@ inqueue(): 
//------------------------------------------------------------------
template<class T> void LinkList<T>::inqueue(T &_info) 
{  LinkItem<T> *t;

   t = new LinkItem<T>(_info);
   inqueue(t);
}


//@ dequeue():
//------------------------------------------------------------------
template<class T> T LinkList<T>::dequeue()
{  LinkItem<T> *h1, *h2;
   T temp;

   h1 = head->pos; h2 = h1->pos;
   head->pos = h2; h2->pre = head; 
   h1->pos = h1->pre = 0;
   temp = h1->info;
   delete h1;
   length--;
   return temp;
}


//@ find(): devuelve al item que contiene la llave, 0 si falla
//------------------------------------------------------------------
template<class T> T *LinkList<T>::find(float _key) 
{  LinkItem<T> *h1, *h2;

   h2 = head;
   h1 = h2->pos;
   while ((h1!=tail)&&(h1->key!=_key))
   {  h2 = h1; h1 = h1->pos;
   };
   if (h1!=tail)
      return &(h1->info);
   else
      return 0;
}


//@ next(): devuelve el siguiente item sin visitar, 0 si acabo
//------------------------------------------------------------------
template<class T> T *LinkList<T>::next() 
{  LinkItem<T> *h1, *h2;
   T temp;

   h2 = head;
   h1 = h2->pos;
   while ((h1!=tail)&&(h1->isMarked()))
   {  h2 = h1; h1 = h1->pos;
   };
   if (h1!=tail)
   {  h1->setMark();
      return &(h1->info);
   }
   else
   {  h2 = head;
      h1 = h2->pos;
      while (h1!=tail)
      {  h1->resetMark();
         h2 = h1; h1 = h1->pos;
      };
      return 0;			
   };
}

//@ next(): tambien devuelve su llave de orden, como efecto lateral.
//------------------------------------------------------------------
template<class T> T *LinkList<T>::next(float &_key) 
{  LinkItem<T> *h1, *h2;
   T temp;

   h2 = head;
   h1 = h2->pos;
   while ((h1!=tail)&&(h1->isMarked()))
   {  h2 = h1; h1 = h1->pos;
   };
   if (h1!=tail)
   {  h1->setMark();
      _key = h1->key;
      return &(h1->info);
   }
   else
   {  h2 = head;
      h1 = h2->pos;
      while (h1!=tail)
      {  h1->resetMark();
         h2 = h1; h1 = h1->pos;
      };
      return 0;			
   };
}

#endif



