#include "DLL.h"

//----------------------------------------------------------------------
//  Operaciones Lista doblemente enlazada
//----------------------------------------------------------------------

static Node* new_node( Producto *p, size_t cant ) 
{

      Node* n = malloc( sizeof( Node ) );

      if( n != NULL ) 
      {

         n->item.cantidad = cant;
         n->next = NULL;
         n->prev = NULL;
         n->item.bar_code = p->bar_code;
         n->item.precio = p->precio;
         strcpy( n->item.nombre, p->nombre );
      }

      return n; 
}


static void reset( DLL* this ) 
{

      this->first = this->last = this->cursor = NULL;
      this->len = 0;
}


bool DLL_IsEmpty( DLL* this ) 
{

      assert( this != NULL );
      return ( this->len == 0 );
}


DLL* DLL_New() 
{

      DLL* lista = ( DLL* ) malloc( sizeof( DLL ));

      if( lista != NULL ) {

            reset( lista );
      }

      return lista;
}


bool DLL_Delete( DLL** this ) 
{

      bool done = false;
      if( *this != NULL ) 
      {

            DLL* lista = *this;
            while( lista->len != 0 ) 
            {

                  Node* tmp = lista->first->next;
                  free( lista->first );
                  lista->first = tmp;
                  --lista->len;
            }

            reset( lista ); 
            free( lista );
            *this = NULL;
            done = true;
      }

      return done;
}


void DLL_InsertBack( DLL* this, Producto * p, size_t cant ) 
{

      assert( this != NULL );

      Node* n = new_node( p, cant );
      if( n != NULL ) 
      {

            if( DLL_IsEmpty( this ) == true ) 
            { 
                  this->first = this->last = this->cursor = n;
            } 
            else 
            {

                  this->last->next = n; 
                  n->prev = this->last; 
                  this->last = n;
            }

            ++this->len;
      }
}

void DLL_InsertFront( DLL* this, Producto * p, size_t cant ) 
{

      assert( this != NULL );

      Node* n = new_node( p, cant );
      if( n != NULL ) 
      {

            if( DLL_IsEmpty( this ) == true ) 
            { 

                  this->first = this->last = this->cursor = n;
            } 
            else 
            {

                  this->first->prev = n; 
                  n->next = this->first; 
                  this->first = n;
            }

            ++this->len;
      }
}
static void DLL_RemoveFront( DLL* this ) 
{

      assert( this != NULL );

      if( DLL_IsEmpty( this ) == false ) 
      {

            Node* tmp = this->first->next;
            free( this->first );
            this->first = tmp;
            this->first->prev = NULL;
            --this->len;
      }      
}


static void DLL_RemoveBack( DLL* this ) 
{

      assert( this != NULL );

      if( DLL_IsEmpty( this ) == false ) 
      {

            Node* tmp = this->last->prev;
            free( this->last );
            this->last = tmp;
            this->last->next = NULL;
            --this->len;

      }    
}


Producto DLL_Remove( DLL* this ) 
{

      assert( this != NULL );
      Producto p;

      if( DLL_IsEmpty( this ) == false && this->cursor != NULL ) 
      {

            Node* tmp_next = this->cursor->next;
            Node* tmp_prev = this->cursor->prev;

            p.bar_code = this->cursor->item.bar_code;
            strcpy( p.nombre, this->cursor->item.nombre );
            p.precio = this->cursor->item.precio;

            if( this->cursor->item.cantidad > 1 ) 
            {

                  --this->cursor->item.cantidad;
                  p.cantidad = this->cursor->item.cantidad;
            } 
            else 
            {

                  if( tmp_next == NULL && tmp_prev == NULL ) 
                  {

                        free( this->cursor );
                        reset( this ); 
                  } else if( this->cursor == this->first ) 
                  {

                        DLL_RemoveFront( this );
                        this->cursor = this->first;

                  } else if( this->cursor == this->last )
                  {

                        DLL_RemoveBack( this );
                        this->cursor = this->last;

                  } 
                  else 
                  {

                        free( this->cursor );
                        this->cursor = tmp_prev;
                        this->cursor->next = tmp_next;
                        tmp_next->prev = this->cursor;
                        --this->len;
                  }
            }
      }

      return p;
}

/**
 * @brief Busca un producto del Inventario por barcode y pone el cursor en el producto(nodo de la DLL)
 * 
 * @param this Referencia a un objeto Stock
 */
bool DLL_Search( DLL* this, int bar_code ) 
{

      assert( this != NULL );
      bool done = false; 

      if( this->len != 0 ) 
      {

            for( Node* tmp = this->first; tmp != NULL; tmp = tmp->next ) 
            {

                  if( tmp->item.bar_code == bar_code ) 
                  {

                        this->cursor = tmp;
                        done = true;
                        return done;
                  }
            }
      }

      return done;
}


Producto DLL_Peek( DLL* this ) 
{

      assert( this != NULL );
      Producto p;

      if( DLL_IsEmpty( this ) == false && this->cursor != NULL ) 
      {

            p.bar_code = this->cursor->item.bar_code;
            strcpy( p.nombre, this->cursor->item.nombre );  
            p.precio = this->cursor->item.precio;
            p.cantidad = this->cursor->item.cantidad;
      }

      return p;
}


bool DLL_Print( DLL* this ) 
{

      assert( this != NULL );

      bool done = false;
      if( DLL_IsEmpty( this ) == false ) 
      {

            FILE *inventario;

            inventario = fopen( "Inventario.txt","w+" );

            if( inventario != NULL ) done = true;

            printf("\n\t\tReporte\n\n");
            fputs( "Producto\t", inventario );
            fputs( "Cantidad\t", inventario );
            fputs( "Codigo de barra\t\t", inventario );
            fputs( "Precio\n", inventario);

            for( Node* it = this->first; it != NULL; it = it->next ) {

                  printf("Producto: %s\n", it->item.nombre );
                  printf("Cantidad: %li\n", it->item.cantidad );
                  printf("Codigo de barras: %i\n", it->item.bar_code );
                  printf("Precio: %.2f\n\n", it->item.precio );
                  fprintf( inventario, "%s\t\t", it->item.nombre );
                  fprintf( inventario, "%li\t\t", it->item.cantidad );
                  fprintf( inventario, "%i\t\t\t", it->item.bar_code );
                  fprintf( inventario, "%.2f\n", it->item.precio );
            }

            fclose( inventario );
      }

      return done;
}


void DLL_MakeEmpty( DLL* this ) 
{

      assert( this != NULL );
      while( this->len != 0 ) 
      {

            Node* tmp = this->first->next;
            free( this->first );
            this->first = tmp;
            --this->len;
      }

      reset( this );
}


void DLL_PIB( DLL* this, float *income ) 
{

      if( this->len != 0 ) 
      {

            for( Node* tmp = this->first; tmp != NULL; tmp = tmp->next ) 
            {
                  *income = *income + ( tmp->item.precio * tmp->item.cantidad );
            }
      }
}


static size_t DLL_Contador( DLL* this, Node* n ) 
{

      assert( n != NULL );

      Node* tmp = n;
      size_t i = 0;

      while( tmp != this->first ) 
      {
            tmp = tmp->prev;
            i++;
      }
      return i;
} 

void swap(Node* node1, Node* node2) 
{
      int temp = node1->item.cantidad;
      int temp2 = node1->item.bar_code;
      int temp3 = node1->item.precio;
      char tmp4[MAX];
      strcpy(tmp4, node1->item.nombre);

      node1->item.cantidad = node2->item.cantidad;
      node1->item.bar_code = node2->item.bar_code;
      node1->item.precio = node2->item.precio;
      strcpy(node1->item.nombre, node2->item.nombre);

      node2->item.cantidad = temp;
      node2->item.bar_code = temp2;
      node2->item.precio = temp3;
      strcpy(node2->item.nombre, tmp4);
}

void DLL_BubbleSort(DLL* this) 
{
    if (this == NULL || this->first == NULL || this->first->next == NULL) {
        // La lista está vacía o tiene solo un nodo
        return;
    }
      
    bool swapped;
    Node* currentNode;
    do 
    {
        swapped = false;
        currentNode = this->first;
          while (currentNode->next != NULL) 
          {
            if (currentNode->item.cantidad > currentNode->next->item.cantidad) 
            {
                swap(currentNode, currentNode->next);
                swapped = true;
            }
            currentNode = currentNode->next;
        }
    } while (swapped);
}