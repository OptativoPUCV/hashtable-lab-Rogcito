#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value){
    Pair*nuevoDato=createPair(key,value);
    long i;
    i=hash(key,map->capacity);
    while(map->buckets[i]!=NULL){
      if(i+1==map->capacity){
        i=0;
      }
      if(map->buckets[i]->key==NULL){
        break;
      }
      i++;
    }
    map->buckets[i]=nuevoDato;
    map->current=i;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
    HashMap*nuevo=(HashMap*)malloc(sizeof(HashMap));
    nuevo->buckets=(Pair**)malloc(capacity*sizeof(Pair));
    nuevo->capacity=capacity;
    nuevo->size=0;
    nuevo->current=-1;
    return nuevo;
}

void eraseMap(HashMap * map,  char * key) {    
  

}

void * searchMap(HashMap * map,  char * key) {
    long i=hash(key,map->capacity);
    while(map->buckets[i]!=NULL){
      if(strncmp(map->buckets[i]->key,key,10)){
        map->current=i;
        return map->buckets[i]->value;
      }
      if(i+1==map->capacity){
        i=0;
      }
      i++;
    }
    map->current=i;   
    return NULL;
}

void * firstMap(HashMap * map) {
    return NULL;
}

void * nextMap(HashMap * map) {
    return NULL;
}
