#ifndef STOCK_INC
#define STOCK_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "DLL.h"


//----------------------------------------------------------------------
//  Inventario
//----------------------------------------------------------------------

typedef struct Stock
{
      DLL* list;
} Stock; // <- Stock = Inventario

/**
 * @brief Crea un Inventario
 * 
 * @return Devuelve una variable Stock* 
 */
Stock* Stock_new();

/**
 * @brief Elimina el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @return true Si se elimino el inventario, false No se elimino el inventario
 */
bool Stock_delete( Stock* this );

/**
 * @brief Añade un producto a el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 * @param cant Cantidad a añadir
 */
void Stock_add( Stock* this, Producto* p, size_t cant );

/**
 * @brief Retira un producto del Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 */
void Stock_remove( Stock* this, Producto* p );

/**
 * @brief Busca un producto en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool Stock_search( Stock* this, Producto* p );

/**
 * @brief Busca un producto en el inventario mediante su codigo de barras.
 * 
 * @param this Referencia a un objeto Stock
 * @param bar_code Codigo de barras del producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool Stock_search_by_bar_code( Stock* this, int bar_code );

/**
 * @brief Obtiene una copia de un producto
 * 
 * @param this Referencia a un objeto Stock
 * @return Producto Regresa un producto
 */
Producto Stock_get( Stock* this );

/**
 * @brief Realiza un reporte de los productos que se encuntran en el inventario
 * 
 * @param this Referencia a un objeto Stock
 * @return true Se hizo el reporte, false No se hizo el reporte
 */
bool Stock_report( Stock* this );

/**
 * @brief Elimina todos los productos del inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Stock_MakeEmpty( Stock* this );

/**
 * @brief Realiza la suma del valor de los productos almacenados en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param dinero Variable puntero en donde se almacena la suma
 */
void Stock_PIB( Stock* this, float *dinero );

/**
 * @brief Ordena los productos del inventario acorde a su cantidad
 * 
 * @param this Referencia a un objeto Stock
 * @return true El inventario se ordeno, false El inventario no se ordeno
 */
bool Stock_Ordenamiento( Stock* this );



#endif   /* ----- #ifndef STOCK_INC  ----- */