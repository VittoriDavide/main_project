//
//  Vector.h
//  APA 2
//
//  Created by David Vittori on 11/8/16.
//  Copyright © 2016 David Vittori. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//ADT di un Vettore generico

typedef void (*VectorFreeFunction)(void *elemAddr);

typedef int (*VectorCompareFunction)(const void *elemAddr, const void * elemAddr2);

typedef void (*VectorMapFunction)(const void *elemAddr, const void * elemAddr2);

typedef bool (*VectorFilterFunction)(const void *elemAddr);


//Struct del Vettore
typedef struct{
    void *elems;
    int logLenth;
    int elemSize;
    long allocLength;
    VectorFreeFunction freefn;
}vector;

//Funzione per creare un vettore nuovo 
void VectorNew(vector *v, int elemSize, VectorFreeFunction freefn, int allocLength);

//Funzione per distruggere un vettore
void VectorDispose(vector *v);

//funzione per inserire un elemento nella posizione indicata
void VectorInsert(vector *v,const void *elemAddr, int pos);

//funzione per inserire alla fine del vettore
void VectorAppend(vector *v, const void * elemAddr);

//restituisce l'elemento nella posizione indicata
void *VectorNth(vector *v, int position);

//funzione per ordinare un vettore
void VectorSort(vector *v, VectorCompareFunction compare);

//funzione per mappare un vettore
void VectorMap(vector *v,VectorMapFunction mapfn, void * aux);

//funzione per la ricerca di un elemento, sono implementate due funzioni. Una lineare e una dicotomica in maniera tale di avere una funzone optimizata
long VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted);

//restituisce la lunghezza del vettore
int VectorLength(vector *vec);

//Elimina una cella del vettore
void VectorDelete(vector *vec,int pos);

/**
 * Function: VectorReplace
 * -----------------------
 * Overwrites the element at the specified position with a new value.  Before
 * being overwritten, the VectorFreeFunction that was supplied to VectorNew is levied
 * against the old element.  Then that position in the vector will get a new value by
 * copying the new element's contents from the memory pointed to by elemAddr.
 * An assert is raised if n is less than 0 or greater than the logical length
 * minus one.  None of the other elements are affected or rearranged by this
 * operation, and the size of the vector remains constant. This method must
 * operate in constant time.
 */

void VectorReplace(vector *v, const void *elemAddr, int position);

/**
 *
 * Function: Filter
 * ----------------
 * Delete all the elements that doesnt agree with the function 
 *
 */

void VectorFilter(vector * vec, VectorFilterFunction filterfn);

#endif /* Vector_h */
