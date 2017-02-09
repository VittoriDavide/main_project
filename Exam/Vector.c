//
//  Vector.c
//  APA 2
//
//  Created by David Vittori on 11/8/16.
//  Copyright © 2016 David Vittori. All rights reserved.
//

#include "Vector.h"
#include <stdlib.h>
#include <stdbool.h>
#include <search.h>

void VectorNew(vector *v, int elemSize,VectorFreeFunction freefn ,int allocLength)
{
    v->elemSize = elemSize;
    v->allocLength = allocLength;
    v->elems = malloc(v->elemSize*v->allocLength);
    v->freefn = freefn;
    v->logLenth = 0;
}

void VectorDispose(vector *vec){
    
    if(vec->freefn){
        for (int i = vec->logLenth - 1; i >= 0; i--) {
            vec->freefn(((char *)vec->elems + i*vec->elemSize));
        }
    }
    free(vec->elems);

}

static void vectorGrow(vector *v){
    v->allocLength *= 2;
    v->elems = reallocf((char *)v->elems, v->allocLength*v->elemSize);
}

void VectorInsert(vector *v,const void *elem, int pos)
{
    assert(pos >= 0 || pos <= v->logLenth);
    
    if (v->logLenth == v->allocLength)vectorGrow(v);
    size_t backSize = ((char *)v->elems + (v->logLenth)*v->elemSize) - ((char *)v->elems + pos*v->elemSize);
    memmove((char *)v->elems + v->elemSize*(pos+1),(char *)v->elems + v->elemSize*(pos), backSize);
    memcpy((char *)v->elems + v->elemSize*pos,elem,v->elemSize);
    v->logLenth++;
    
}
void VectorDelete(vector *v,int pos){
    assert(pos >= 0 && pos <= v->logLenth);
    
    size_t backSize = ((char *)v->elems + v->logLenth*v->elemSize) - ((char *)v->elems + (pos+1)*v->elemSize);
    memmove((char *)v->elems + v->elemSize*(pos),v->elems + v->elemSize*(pos+1), backSize);
    v->logLenth--;

}

void *VectorNth(vector *v, int position)
{
    if(position < 0 || position > v->logLenth)
        return NULL;
    
    return (char *)v->elems + v->elemSize*position;
}

void VectorMap(vector *v,VectorMapFunction mapfn, void * aux){
    assert(mapfn);
    for (int i = 0; i < v->logLenth; i++) {
        mapfn(v->elems + i*v->elemSize,aux);
    }
}

void VectorSort(vector *v, VectorCompareFunction compare)
{ qsort(v->elems,v->logLenth,v->elemSize,compare); }


void VectorAppend(vector *v, const void * elemAddr)
{
    if (v->logLenth >= v->allocLength)vectorGrow(v);
    memcpy((char *)v->elems + v->elemSize*v->logLenth,elemAddr,v->elemSize);
    v->logLenth++;

}

int VectorLength(vector *vec){
    return vec->logLenth;
}

const void *find(const void *key, const void *base, size_t length, size_t size, VectorCompareFunction cmpfn)
{
    for(int i = 0; i < length; i++){
        if(cmpfn(key,base +i*size) == 0)return base +i*size;
    }
    return NULL;
}

static const int kNotFound = -1;
long VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
    assert(startIndex <= v->logLenth && startIndex >= 0 && key && searchFn);
    void *ret;
    if (isSorted)
        ret = bsearch(key, (char *)v->elems + startIndex*v->elemSize, v->logLenth-startIndex, v->elemSize, searchFn);
    else{
        ret = find(key, (char *)v->elems + startIndex*v->elemSize,v->logLenth-startIndex,v->elemSize,searchFn);
    }

    return (ret) ? ((char *)ret - (char *)v->elems)/v->elemSize : kNotFound;
    //if ret is NULL return false, if not return the matching position. Dividiamo per v->elemSize perche il numero che ci ritorna la sottrazione e in bytes

}

void VectorFilter(vector * vec, VectorFilterFunction filterfn)
{
    int i;
    for( i = vec->logLenth-1; i >= 0 ; i--){
        if(!filterfn(vec->elems + i*vec->elemSize)){
            VectorDelete(vec, i);
        }
    }
}

void VectorReplace(vector *v, const void *elemAddr, int position){
    
    assert(position >= 0 && position <= v->logLenth-1);
    memcpy((char *)v->elems + position *v->elemSize , elemAddr, v->elemSize);

}
