#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#ifndef DLL_INC
#define DLL_INC
#define MAX 32

//----------------------------------------------------------------------
//  Producto
//----------------------------------------------------------------------

typedef struct Producto
{
      size_t cantidad;
      int bar_code;
      float precio;
      char nombre[MAX];
} Producto;

// Los productos NO tienen operaciones

//----------------------------------------------------------------------
//  Lista doblemente enlazada
//----------------------------------------------------------------------

typedef struct Node 
{
      Producto item;
      struct Node* prev;
      struct Node* next;
} Node;


typedef struct DLL 
{

      Node* first;
      Node* last;
      Node* cursor;
      size_t len;
} DLL;

/**
 * @brief Crea una lista
 * 
 * @return DLL* Una referencia a la lista
 */
DLL* DLL_New();

/**
 * @brief Elimina la lista
 * 
 * @param this Referencia a un objeto DLL
 * @return true Elimino la lista, false No se elimino la lista
 */
bool DLL_Delete( DLL** this );

/**
 * @brief Inserta un objeto producto
 * 
 * @param this Referencia a un objeto DLL
 * @param p Referencia a un objeto Producto
 * @param cant Cantidad de elementos del producto
 */
void DLL_InsertBack( DLL* this, Producto* p, size_t cant );



/**
 * @brief Inserta un objeto producto en el frente
 * 
 * @param this Referencia a un objeto DLL
 * @param p Referencia a un objeto Producto
 * @param cant Cantidad de elementos del producto
 */
void DLL_InsertFront( DLL* this, Producto * p, size_t cant ) ;

/**
 * @brief Retira un producto de la lista, en el caso de su cantidad ser 0 elimina el producto completamente 
 * 
 * @param this Referencia a un objeto DLL
 * @return Producto Referencia a un objeto Producto
 */
Producto DLL_Remove( DLL* this );

/**
 * @brief Busca un Producto en la lista
 * 
 * @param this Referencia a un objeto DLL
 * @param bar_code Codigo de barras del producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool DLL_Search( DLL* this, int bar_code );

/**
 * @brief Realiza una copia de un producto
 * 
 * @param this Referencia a un objeto DLL
 * @return Producto Regresa un producto
 */
Producto DLL_Peek( DLL* this );

/**
 * @brief Imprime el reporte de los productos de la lista en un archivo txt y en pantalla
 * 
 * @param this Referencia a un objeto DLL
 * @return true Se realizo el reporte, false No se realizao el reporte
 */
bool DLL_Print( DLL* this );

/**
 * @brief Elimina los nodos, pero se conserva la lista
 * 
 * @param this Referencia a un objeto DLL
 */
void DLL_MakeEmpty( DLL* this );

/**
 * @brief Pregunta si esta vacia la lista
 * 
 * @param this Referencia a un objeto DLL
 */
bool DLL_IsEmpty( DLL* this );

/**
 * @brief Pone los apuntadores de la DLL en NULL y len=0
 * 
 * @param this Referencia a un objeto DLL
 */
static void reset( DLL* this );

/**
 * @brief Realiza la suma del valor de los productos almacenados en la lista
 * 
 * @param this Referencia a un objeto DLL
 * @param ganan Variable puntero en donde se almacena la suma
 */
void DLL_PIB( DLL* this, float* ganan );

/**
 * @brief Ordena la lista segun la cantidad de los productos
 * 
 * @param this Referencia a un objeto DLL
 * @param primero Referencia a un objeto Nodo
 * @param ultimo Referencia a un objeto Producto
 */
void DLL_BubbleSort(DLL* this);

#endif   /* ----- #ifndef STOCK_INC  ----- */