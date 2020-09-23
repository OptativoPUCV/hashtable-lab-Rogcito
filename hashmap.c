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


void insertMap(HashMap * map, char * key, void * value) {
    Pair*dato=createPair(key,value);
    long i=hash(key,map->capacity);
    while(map->buckets[i]!=NULL){
      if(map->buckets[i]->key==NULL)break;
      if(i==map->capacity-1)i=0;
      i++;
    }
    map->buckets[i]=dato;
    map->size++;
    map->current=i;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair**auxBuckets=map->buckets;
    long auxCapacity=map->capacity;
    map->capacity*=2;
    map->buckets=(Pair**)malloc(map->capacity*sizeof(Pair*));
    map->size=0;
    long i;
    for(i=0;i<auxCapacity;i++){
      if(auxBuckets[i]!=NULL){
        insertMap(map,auxBuckets[i]->key,auxBuckets[i]->value);
      }
    }
}


HashMap * createMap(long capacity) {
    HashMap* nuevo=(HashMap*)malloc(sizeof(HashMap));
    nuevo->buckets=(Pair**)malloc(capacity*sizeof(Pair));
    nuevo->size=0;
    nuevo->capacity=capacity;
    nuevo->current=-1;
    return nuevo;
}

void eraseMap(HashMap * map,  char * key) {    
  long i=hash(key,map->capacity);
  while(map->buckets[i]!=NULL){
      if(strncmp(map->buckets[i]->key,key,20)==0){
        map->current=i;
        map->size--;
        map->buckets[i]->key=NULL;
      }
      if(i==map->capacity-1)i=0;
      i++;
  }

}

void * searchMap(HashMap * map,  char * key) {   
    long i=hash(key,map->capacity);
    while(map->buckets[i]!=NULL){
      if(strncmp(map->buckets[i]->key,key,20)==0){
        map->current=i;
        return map->buckets[i]->value;
      }
      if(i==map->capacity-1)i=0;
      i++;
    }
    map->current=i;
    return NULL;
}

void * firstMap(HashMap * map) {
    long i;
    for(i=0;i<map->capacity;i++){
      if(map->buckets[i]!=NULL && map->buckets[i]->key!=NULL && map->buckets[i]->value!=NULL){
        map->current=i;
        return map->buckets[i]->value;
      }
    }
    return NULL;
}

void * nextMap(HashMap * map) {
    long i;
    for(i=map->current;i<map->capacity;i++){
      if(map->buckets[i+1]!=NULL && map->buckets[i+1]->key!=NULL && map->buckets[i+1]->value!=NULL){
        map->current=i+1;
        return map->buckets[i+1]->value;
      }
    }
    return NULL;
}
