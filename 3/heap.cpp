#include "heap.h"

using namespace std;

heap::heap(int capacity){
  filled = 0;                 //Initialize heap to empty
  this->capacity = capacity;  //Using this pointer to avoid issues with reused names
  data.resize(capacity + 1);  //Resize vector to be M + 1 since heap doesnt start at 0
  mapping = new hashTable(capacity*2);  //HashTable Initialize
}

int heap::insert(const std::string &id, int key, void *pv){
  if(filled == capacity)
    return 1;
  else if(mapping->contains(id))
    return 2;
  else{
    node tmp;   //Set id, key, and pv of new node
    tmp.id = id;
    tmp.key = key;
    tmp.pData = pv;

    mapping->insert(id,&data[filled]);  //Insert Entry into HashTable
    data[++filled] = tmp;   //Increase current filled index and set the node to new node
    percolateUp(filled);    //PercolateUp by the amount of nodes in heap

    return 0;
  }
}

int heap::setKey(const std::string &id, int key){
  if(!(mapping->contains(id)))
    return 1;
  else{
    node *tmp = (node *)mapping->getPointer(id);   //Get pointer from hashTable
    int oldKey = tmp->key;    //Store the oldKey of the node
    tmp->key = key;           //Set the key to the new key

    int i = getPos(tmp);      //Get the position of the current node
    mapping->setPointer(data[i].id, &data[i]);  //Set the new pointer in the HashTable
    //Depending on whether the new key is greator or lower, percolate down or up
    if(key > oldKey)
      percolateDown(i);
    else if(oldKey > key)
      percolateUp(i);

    return 0;
  }
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
  if(filled == 0)
    return 1;
  else{
    //Setting all inputs of deleteMin to deleted values if provided
    if(pId != nullptr)
      *pId = data[1].id;
    if(pKey != nullptr)
      *pKey = data[1].key;
    if(ppData != nullptr)
      *(void **)ppData = data[1].pData;
    //Using Index 1 since 1st node has lowest key
    mapping->remove(data[1].id);  //Remove node from Hashtable
    data[1] = data[filled--];     //set min to current last index and percolate
    percolateDown(1);             //PercolateDown by 1 since deleting 1st node
    return 0;
  }
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
  if(!(mapping->contains(id)))
    return 1;
  else{
    node *tmp = (node *)mapping->getPointer(id);  //Get pointer from hashTable
    //Setting values to provided addresses
    if(pKey != nullptr)
      *pKey = tmp->key;
    if(ppData != nullptr)
      *(void **)ppData = tmp->pData;

    int tmpkey = tmp->key;  //Check Key of Node to be Deleted
    mapping->remove(id);    //Remove node from Hashtable
    *tmp = data[filled--];  //Set TempNode to last indexed node
    int newKey = tmp->key;  //Check Key of Current TempNode
    int i = getPos(tmp);
    //Percolate depending on inequality of newKey and tmpkey
    if(newKey > tmpkey)
      percolateDown(i);
    else if(tmpkey > newKey)
      percolateUp(i);

    return 0;
  }
}

void heap::percolateUp(int posCur){
  node tmp = data[posCur];   //Store the node of the provided position
	int parent = posCur / 2;   //Parent node is Current Position / 2
	while(posCur > 1 && (tmp.key) < (data[parent].key)){
		data[posCur] = data[parent];
		mapping->setPointer(data[posCur].id, &data[posCur]);
		posCur = parent;        //Loop by setting current position to parent position
		parent = posCur / 2;    //Parent node is Current Position / 2
	}
  //Set the current position to the node to be percolated
	data[posCur] = tmp;
  //Set the pointer of the percolated entry
	mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
  node tmp = data[posCur];  //Store the node of the provided position
  int child = posCur * 2;   //Child node is Current Position * 2
  while(posCur * 2 <= filled){
    child = posCur * 2;     //Child node is Current Position * 2
    if(child < filled && data[child + 1].key < data[child].key)
      ++child;
    if(data[child].key < tmp.key){
      data[posCur] = data[child];
      mapping->setPointer(data[posCur].id, &data[posCur]);
    } else
      break;
    posCur = child;   //Loop by setting current position to child position
  }
  //Set the current position to the node to be percolated
  data[posCur] = tmp;
  //Set the pointer of the percolated entry
	mapping->setPointer(data[posCur].id, &data[posCur]);
}

// Provided getPos function
int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}
