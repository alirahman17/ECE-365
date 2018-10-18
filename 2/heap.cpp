#include "heap.h"

heap::heap(int capacity){
  filled = 0;
  this->capacity = capacity;
  data.resize(capacity + 1);
  mapping = new hashTable(capacity*2);
}

int heap::insert(const std::string &id, int key, void *pv){
  if(!(filled < capacity))
    return 1;
  else if(map->contains(id))
    return 2;
  else{
    node tmp;
    tmp.id = id;
    tmp.key = key;
    tmp.pData = pv;

    mapping->insert(id,pv);
    data[++filled] = tmp;
    percolateUp(filled);

    return 0;
  }
}

int heap::setKey(const std::string &id, int key){
  if(!(mapping->contains(id)))
    return 1;
  else{
    node *tmp = (node *)mapping->getPointer(id);
    int oldKey = tmp->key;
    tmp->key = key;

    int i = getPos(tmp);
    mapping->setPointer(data[i].id, &data[i]);

    if(key > oldKey)
      percolateDown(i);
    else if(oldKey > key)
      percolateUp(i);

    return 0;
  }
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
  if(!filled)
    return 1;
  else{

  }
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
  if(!(mapping->contains(id)))
    return 1;
  else{

  }
}

void heap::percolateUp(int posCur){

}

void heap::percolateDown(int posCur){

}

int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}
