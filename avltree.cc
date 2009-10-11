// Archivo: avltree.cc
// implementacion de las clases parametrizadas 'AVLItem' y 'AVLTree'
// R. Marcelin J. (21/06/99)

#if !defined (__AVLTREE_)
#define __AVLTREE_

#include <iostream>

//#include "trace.h"                    // para rastrear operaciones
//DEFINE_TRACE_MODULE(avl, "avl");

template <class T> class AVLItem;     // item de un arbol balanceado
template <class T> class AVLTree;     // Adelson, Velski y Landis

template <class T> class AVLItem       
{  public:
      AVLItem();                       // constructor 
      AVLItem(T &_info);               // constructor 
      AVLItem(T &_info, float _key);   // constructor 
      ~AVLItem();                      // destructor 

   private:
      float key;                       // para establecer un orden
      T info;                          // campo de informacion
      int bal;                         // altura izq - altura der : -1,0,1
      AVLItem *pre;                    // vecino izquierdo
      AVLItem *pos;                    // vecino derecho
      friend class AVLTree<T>;         // acceso a los atrib. privados

};




                                       // se usa en AVLTree 
enum search {FAIL   = 0 ,              // no lo encontro
             EUREKA = 1 ,              // lo encontro en un hijo 
             LFOUND = 2 ,              // es descendiente de un hijo izq.
             RFOUND = 3 };             // es descendiente de un hijo der.

template <class T> class AVLTree       // eficiente para ~miles de items
{  public:
      // constructor
      AVLTree();                       

      // Destructor
      ~AVLTree();                      

      // total de items insertados
      int getSize();                  

      // verdadero si el arbol esta vacio
      int isEmpty();                  
      
      // descenso recursivo en preorden, desde la raiz
      void visit(AVLItem<T> *t, int nivel);  
      void visit();                    
      
      // balancea arbol podado por la izquierda
      AVLItem<T> *lbalance(AVLItem<T> *t);

      // balancea arbol podado por la derecha
      AVLItem<T> *rbalance(AVLItem<T> *t);

      // incrementa el arbol y verifica su balance
      void insert(T &_info);
      void insert(T &_info, float _key);
      void insert(AVLItem<T> *n);     
      AVLItem<T> *insert(AVLItem<T> *n, AVLItem<T> *t);

      // devuelve el item con la menor clave de todo el arbol
      // usar con isEmpty() 
      T minval();                    
      T minval(AVLItem<T> *t, enum search &result);
      
      // busca al item con la mayor clave de un subarbol  
      AVLItem<T> *maxval(AVLItem<T> *t, T &_info, enum search &result);
      
      // elimina un item particular, segun su llave
      int remove(float _key);       
      enum search remove(float _key, AVLItem<T> *t);

      // devuelve ap. a item que busca por su llave, 0 en otro caso
      T *find(float _key);
      T *find(float _key, AVLItem<T> *t);

   private:
      AVLItem<T> *root;                // ra¡z
      int size;                        // taman~o del arbol
      int balance;                     // 1 si debe verificarse el balance
};





//@ AVLItem(): constructor por omision
//------------------------------------------------------------------
template<class T> AVLItem<T>::AVLItem()                        
{  key        = -1;
   pos        =  0;
   pre        =  0;
   bal        =  0;                                 
//   TRACE(avl, -1, ("AVLItem constructor\n"));
}


//@ AVLItem(): constructor para tipos basicos
//------------------------------------------------------------------
template<class T> AVLItem<T>::AVLItem(T &_info)                 
{  info       = _info;
   key        = _info; 
   pos        = 0;
   pre        = 0;        
   bal        = 0;           
//   TRACE(avl, -1, ("AVLItem constructor\n"));
}

//@ AVLItem(): constructor para clases
//             es mejor inicializar por fuera un miembro compuesto
//------------------------------------------------------------------
template<class T> AVLItem<T>::AVLItem(T &_info, float _key) : info(_info)  
{  key        = _key; 
   pos        = 0;
   pre        = 0;        
   bal        = 0;           
//   TRACE(avl, -1, ("AVLItem constructor\n"));
}


//@ ~AVLItem(): destructor
// -----------------------------------------------------------------
template <class T> AVLItem<T>::~AVLItem()                       
{  
// TRACE(avl, -1, ("AVLItem destructor\n"));                       
}





// AVLTree(): Constructor
// -----------------------------------------------------------------
template<class T> AVLTree<T>::AVLTree()                        
{  root = 0;
   size = 0;
   balance = 0;
//   TRACE(avl, -1, ("AVLTree constructor\n"));
}


// AVLTree(): Destructor
// -----------------------------------------------------------------
template<class T> AVLTree<T>::~AVLTree()                       
{  
// TRACE(avl, -1, ("AVLTree destructor\n"));                       
}


// getSize(): total de items insertados
// -----------------------------------------------------------------
template<class T> int AVLTree<T>::getSize()                    
{  return size;                                                    }


// isEmpty(): verdadero si el arbol esta vacio
// -----------------------------------------------------------------
template<class T> int AVLTree<T>::isEmpty()                    
{  return (root == 0);                                             }


// visit(): comienza  por la ra¡z
// -----------------------------------------------------------------
template<class T> void AVLTree<T>::visit()                     
{  visit(root, 0);                                                 }


// visit(): descenso rec. en preorden, imprime contenido y profundidad
// -----------------------------------------------------------------
template<class T> void AVLTree<T>::visit(AVLItem<T> *t, int nivel)  
{                                
  if (t != 0)                   
  {  visit(t->pre, nivel+1);    
     std::cout << t->key << ":" << nivel << ":" << t->bal << "\n";
     visit(t->pos, nivel+1);
  };
}


// lbalance(): balancea un arbol podado por la izquierda
// -----------------------------------------------------------------
template<class T> AVLItem<T> *AVLTree<T>::lbalance(AVLItem<T> *t)
{  AVLItem<T> *t1,*t2, *t3;       
   int b2, b3;                   

   t1 = t;
   switch (t1->bal)
   {  case -1: t1->bal =  0; break;
      case  0: t1->bal =  1; balance = 0; break;
      case  1: t2 = t1->pos; b2 = t2->bal;
               if (b2 >= 0)            // rotaci¢n simple RR
               {  t1->pos = t2->pre; t2->pre = t1;
                  if (b2 == 0)
                  {  t1->bal =  1; t2->bal = -1; balance = 0;     }
                  else
                  {  t1->bal = 0; t2->bal =  0;                   };
                  t1 = t2;
               }
               else                     // rotaci¢n doble RL
               {  t3 = t2->pre; b3 = t3->bal;
                  t2->pre = t3->pos; t3->pos = t2;
                  t1->pos = t3->pre; t3->pre = t1;
                  t1->bal = (b3 ==  1)? -1: 0;
                  t2->bal = (b3 == -1)?  1: 0;
                  t3->bal = 0;
                  t1 = t3;
               };
   };
   return t1;
};


// rbalance(): balancea un arbol podado por la derecha
// -----------------------------------------------------------------
template<class T> AVLItem<T> *AVLTree<T>::rbalance(AVLItem<T> *t)
{  AVLItem<T> *t1,*t2, *t3;       
   int b2, b3;                   

   t1 = t;
   switch (t1->bal)
   {  case  1: t1->bal =  0; break;
      case  0: t1->bal = -1; balance = 0; break;
      case -1: t2 = t1->pre; b2 = t2->bal;
               if (b2 <= 0)            // rotaci¢n simple LL
               {  t1->pre = t2->pos; t2->pos = t1;
                  if (b2 == 0)
                  {  t1->bal = -1; t2->bal =  1; balance = 0;     }
                  else
                  {  t1->bal = 0; t2->bal =  0;                   };
                  t1 = t2;
               }
               else                     // rotaci¢n doble LR
               {  t3 = t2->pos; b3 = t3->bal;
                  t2->pos = t3->pre; t3->pre = t2;
                  t1->pre = t3->pos; t3->pos = t1;
                  t1->bal = (b3 == -1)?  1: 0;
                  t2->bal = (b3 ==  1)? -1: 0;
                  t3->bal = 0;
                  t1 = t3;
               };
   };
   return t1;
};


// insert(): comienza exploracion por la ra¡z
// -----------------------------------------------------------------
template<class T> void AVLTree<T>::insert(T &_info)       
{  AVLItem<T> *n;

   n = new AVLItem<T>(_info);
   root = insert(n, root);                                        
}
      

// insert(): comienza exploracion por la ra¡z
// -----------------------------------------------------------------
template<class T> void AVLTree<T>::insert(T &_info, float _key)       
{  AVLItem<T> *n;

   n = new AVLItem<T>(_info, _key);
   root = insert(n, root);                                        
}
      

// insert(): comienza exploracion por la ra¡z
// -----------------------------------------------------------------
template<class T> void AVLTree<T>::insert(AVLItem<T> *n)       
{  root = insert(n, root);                                        }
      

// insert(): devuelve ap. al subarbol incrementado y rebalanceado.
// -----------------------------------------------------------------
template<class T> AVLItem<T> *AVLTree<T>::insert(AVLItem<T> *n, AVLItem<T> *t)
{  AVLItem<T> *t1, *t2, *t3;      
                                       
   t1 = t;                       
   if (t1 == 0)                         
   {  t1 = n; balance = 1; size++;      // primera vez

   }
   else
     if (n->key < t1->key)              // sin el =
   {  t1->pre = insert(n, t1->pre);     // desciende por la izquierda
      if (balance)
      {  switch(t1->bal)
         {  case  1: t1->bal =  0;  balance = 0;  break;
            case  0: t1->bal = -1;  break;
            case -1: t2 = t1->pre;     
                     if (t2->bal == -1) // rot. simple LL
                     {  t1->pre = t2->pos; t2->pos = t1;
                        t1->bal = 0;
                        t1 = t2;
                     }
                     else
                     {  t3 = t2->pos;   // rot. doble LR
                        t2->pos = t3->pre; t3->pre = t2;
                        t1->pre = t3->pos; t3->pos = t1;
                        t1->bal = (t3->bal == -1)?  1: 0;
                        t2->bal = (t3->bal ==  1)? -1: 0;
                        t1 = t3;
                     };
                     t1->bal = 0;
                     balance = 0;
                           
         };
      };
   }
   else
   {  t1->pos = insert(n, t1->pos);     // desciende por la derecha
      if (balance)
      {  switch(t1->bal)
         {  case -1: t1->bal = 0;   balance = 0;   break;
            case  0: t1->bal = 1;   break;
            case  1: t2 = t1->pos;
                     if (t2->bal == 1)  // rot. simple RR 
                     {  t1->pos = t2->pre; t2->pre = t1;
                        t1->bal = 0;
                        t1 = t2;
                     }
                     else
                     {  t3 = t2->pre;   // rot. doble RL
                        t2->pre = t3->pos; t3->pos = t2;
                        t1->pos = t3->pre; t3->pre = t1;
                        t1->bal = (t3->bal ==  1)? -1: 0;
                        t2->bal = (t3->bal == -1)?  1: 0;
                        t1 = t3;
                     };
                     t1->bal = 0;
                     balance = 0;
         };
      };
   };
   return t1;
};


// minval(): devuelve el item con la menor llave de todo el arbol
// -----------------------------------------------------------------
template<class T> T AVLTree<T>::minval()                      
{  enum search result = FAIL;    
   T _info;
   AVLItem<T> *t;

   if (root->pre == 0)
   {  t = root;
      _info = root->info;  
      root = root->pos;                       
      result = EUREKA;
      delete t;
   }
   else 
      _info = minval(root, result);

   if (result != FAIL) size--;
   return _info;
};


// minval(): descenso rec. por el lado izquierdo
// -----------------------------------------------------------------
template<class T> T AVLTree<T>::minval(AVLItem<T> *t, enum search &result)
{  AVLItem<T> *t1, *t2;          
   T _info;

   t1 = t;
   if (t1->pre == 0)
   {  _info = t->info;
      result = EUREKA;
   }
   else
   {  _info = minval(t1->pre, result);
      if (result == LFOUND)
      {  if (balance) t1->pre = lbalance(t1->pre);
      }
      else
      if (result == EUREKA)
      {  t2 = t1->pre;           // procede a podar a su hijo menor
         t1->pre = t2->pos;      // y lo borra
         result = LFOUND;
         delete t2;
         balance = 1;
      };
   };

   return _info;
};


// maxval(): busca al item con la mayor clave de un subarbol
// -----------------------------------------------------------------
template<class T> AVLItem<T> *AVLTree<T>::maxval(AVLItem<T> *t, T &_info, enum search &result)
{  AVLItem<T> *t1, *t2;          

   t1 = t;
   if (t1->pos == 0)              
   {  _info = t1->info;          // procede a podar a su hijo mayor
      t2 = t1;
      t1 = t1->pre; 
      result = EUREKA;
      delete t2;
      balance = 1; 
   }
   else
   {  t1->pos = maxval(t1->pos, _info, result);
      if (balance) t1 = rbalance(t1);
      result = RFOUND;
   };

   return t1;
};


//@ remove(): inicia la busqueda por la raiz
//------------------------------------------------------------------
template<class T> int AVLTree<T>::remove(float _key)
{  enum search result = FAIL;
   T _info;
   AVLItem<T> *d;

   result = remove(_key, root);            
   if (result == EUREKA)
   {  d = root;
      if (root->pos == 0)  
      {  root = root->pre;
         delete d;
      }
      else
      if (root->pre == 0)  
      {  root = root->pos;
         delete d;
      } 
      else                           
      {  root->pre = maxval(root->pre, _info, result);
         root->setInfo(_info);
         if (balance)  root = lbalance(root);
      };
   }
   else
   if (result == LFOUND)
   {  if (balance) root = lbalance(root);
   }
   else
   if (result == RFOUND)
   {  if (balance) root = rbalance(root);
   };
   if (result != FAIL) size--;
   return result;
};


//@ remove(): elimina a un item segun su llave y verifica el balance
//------------------------------------------------------------------
template<class T> enum search AVLTree<T>::remove(float _key, AVLItem<T> *t)
{  enum search result;
   AVLItem<T> *t1, *t2;
   T _info;

   t1 = t;
   if (t1 == 0)
   {  result = FAIL;                    // no existe
   }
   else
   if (_key == t1->key)
   {  result = EUREKA;                  // "­lo encontre!"
   }
   else
   if (_key < t1->key)
   {  result = remove(_key, t1->pre);      // desciende por la izq.
      if (result == RFOUND)
      {  if (balance) t1->pre = rbalance(t1->pre);                 }
      else
      if (result == LFOUND)
      {  if (balance) t1->pre = lbalance(t1->pre);                 }
      else
      if (result == EUREKA)
      {  t2 = t1->pre;                  
         if (t2->pos == 0)
         {  t1->pre = t2->pre; 
            delete t2;
            balance = 1;
         }
         else
         if (t2->pre == 0)
         {  t1->pre = t2->pos;
            delete t2; 
            balance = 1;
         }
         else                           // el mayor de sus menores
         {  t2->pre=maxval(t2->pre, _info, result);
            t2->setInfo(_info);
            if (balance) t1->pre = lbalance(t1->pre);
         };
      };
      result = LFOUND;
   }
   else
   {  result = remove(_key, t1->pos);      // desciende por la der.
      if (result == RFOUND)
      {  if (balance) t1->pos = rbalance(t1->pos);                 }
      else
      if (result == LFOUND)
      {  if (balance) t1->pos = lbalance(t1->pos);                 }
      else
      if (result == EUREKA)
      {  t2 = t1->pos;
         if (t2->pos == 0)
         {  t1->pos = t2->pre; 
            delete t2;
            balance = 1;
         }
         else
         if (t2->pre == 0)
         {  t1->pos = t2->pos; 
            delete t2;
            balance = 1;
         }
         else                           // el mayor de sus menores
         {  t2->pre=maxval(t2->pre, _info, result);
            t2->setInfo(_info);
            if (balance) t1->pos = lbalance(t1->pos);
         };
      };
      result = RFOUND;
   };

   return result;
};


// find(): 
// -----------------------------------------------------------------
template<class T> T *AVLTree<T>::find(float _key)
{  return find(_key, root);                                         }


// find(): devuelve ap. a item que busca por su llave, 0 en otro caso
// -----------------------------------------------------------------
template<class T> T *AVLTree<T>::find(float _key, AVLItem<T> *t)
{  T *info;      
                                                            
   if (t == 0)                         
      info = 0;                         // no lo encontro
   else
   if (_key == t->key)
      info = &(t->info);                // aqui esta
   else
   if (_key < t->key)
      info = find(_key, t->pre);        // desciende por la izquierda
   else
      info = find(_key, t->pos);        // desciende por la derecha

   return info;
};

#endif
