#include "stock.h"
#include"DLL.h"

//----------------------------------------------------------------------
//  Operaciones Inventario
//----------------------------------------------------------------------

Stock* Stock_new() {

      Stock* lista = ( Stock* ) malloc( sizeof( Stock ) );
      if( lista != NULL ) 
      {

            lista->list = DLL_New();
      }

      return lista;
}


bool Stock_delete( Stock* this ) 
{

      bool done = false;

      if( this != NULL ) {

            DLL* lista = this->list;
            done = DLL_Delete( &lista );
      }

      return done;
}


void Stock_add( Stock* this, Producto* p, size_t cant )
{

      assert( this != NULL );

      if( DLL_Search( this->list, p->bar_code ) == false ) 
      {
            

            DLL_InsertBack( this->list, p, cant );
      } 
      else 
      {

            this->list->cursor->item.cantidad += cant;
      }
}


// quita a un elemento de la lista
void Stock_remove( Stock* this, Producto* p ) 
{

      assert( this != NULL );

      if( DLL_Search( this->list, p->bar_code ) ) 
      {

            *p = DLL_Remove( this->list );
      } 
}


bool Stock_search( Stock* this, Producto* p ) 
{

      assert( this != NULL );

      return DLL_Search( this->list, p->bar_code );
}


bool Stock_search_by_bar_code( Stock* this, int bar_code ) {

      assert( this != NULL );

      return DLL_Search( this->list, bar_code );
}


// devuelve una copia del producto al que apunta el 'cursor'
Producto Stock_get( Stock* this ) {

      assert( this != NULL );

      return DLL_Peek( this->list );
}


bool Stock_report( Stock* this ) {

      assert( this != NULL );

      // imprime todos los productos de la lista
      return DLL_Print( this->list );
}


void Stock_MakeEmpty( Stock* this ) {

      assert( this != NULL );

      DLL_MakeEmpty( this->list );
}


void Stock_PIB( Stock* this, float *dinero ) {

      assert( this != NULL );

      DLL_PIB( this->list , dinero );
}



bool Stock_Ordenamiento( Stock* this ) 
{

      assert( this != NULL );
      bool done = false;

      if( DLL_IsEmpty( this->list ) == false ) 
      {

            done = true;
            DLL_BubbleSort( this->list );
      }

      return done;
}