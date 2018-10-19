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
  else if(mapping->contains(id))
    return 2;
  else{
    node tmp;
    tmp.id = id;
    tmp.key = key;
    tmp.pData = pv;

    mapping->insert(id,&data[filled]);
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
    if(pId != nullptr)
      *pId = data[1].id;
    if(pKey != nullptr)
      *pKey = data[1].key;
    if(ppData != nullptr)
      *(void **)ppData = data[1].pData;

    mapping->remove(data[1].id);
    data[1] = data[filled--];
    percolateDown(1);

    return 0;
  }
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
  if(!(mapping->contains(id)))
    return 1;
  else{
    node *tmp = (node *)mapping->getPointer(id);
    int i = getPos(tmp);

    if(pKey != nullptr)
      *pKey = tmp->key;
    if(ppData != nullptr)
      *(void **)ppData = tmp->pData;

    mapping->remove(id);
    int oldKey = tmp->key;
    data[i] = data[filled--];
    int newKey = tmp->key;

    if(newKey > oldKey)
      percolateDown(i);
    else if(oldKey > newKey)
      percolateUp(i);

    return 0;
  }
}

void heap::percolateUp(int posCur){

  node tmp = data[posCur];
	int parent = posCur/2;
	while(posCur > 1 && (tmp.key) < (data[parent].key)){
		data[posCur] = data[parent];
		mapping->setPointer(data[posCur].id, &data[posCur]);
		posCur = parent;
		parent = posCur / 2;
	}
	data[posCur] = tmp;
	mapping->setPointer(data[posCur].id, &data[posCur]);

}

void heap::percolateDown(int posCur){

  node tmp = data[posCur];
  int child = 0;

  while(posCur *2 <= filled){
    child = posCur * 2;
    if(child < filled && data[child + 1].key < data[child].key)
      ++child;
    if(data[child].key < tmp.key){
      data[posCur] = data[child];
      mapping->setPointer(data[posCur].id, &data[posCur]);
    } else
      break;
    posCur = child;
  }

  data[posCur] = tmp;
	mapping->setPointer(data[posCur].id, &data[posCur]);

}

int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}
