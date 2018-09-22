#include "hash.h"
// DEBUGGING PURPOSES:
#include <iostream>
// END DEBUGGING
using namespace std;

hashTable::hashTable(int size){
  //Constructor
  capacity = getPrime(size*2);
  data.resize(capacity);
  filled = 0;
  //DEBUGGING: cerr << "Capacity = " << capacity << endl;

  for(int i = 0; i < capacity; i++){
    data[i].isOccupied = false;
    data[i].isDeleted = true;
  }
}

int hashTable::insert(const std::string &key, void *pv){
  if(contains(key)){
    return 1;
  }

  int pos = hash(key) % capacity;

  // Collision Detection (Linear Probing)
  while(data[pos].isOccupied){
    pos = (pos + 1) % capacity;
  }

  data[pos].pv = pv;
  data[pos].isOccupied = true;
  data[pos].isDeleted = false;
  data[pos].key = key;
  filled++;

  if(capacity / 2 < filled){
    rehash();
  }

  return 0;
}

bool hashTable::contains(const std::string &key){
  if(findPos(key) != -1){
    return true;
  } else{
    return false;
  }
}

void *hashTable::getPointer(const std::string &key, bool *b){
  int pos = this->findPos(key);
  if(this->contains(key)){
    if(b != nullptr){
      *b = true;
    }
    return data[pos].pv;
  }
  else{
    if(b != nullptr){
      *b = false;
    }
    return nullptr;
  }
}

int hashTable::setPointer(const std::string &key, void *pv){
  int pos = this->findPos(key);
  if(this->contains(key)){
    data[pos].pv = pv;
    return 0;
  }
  else{
    return 1;
  }
}

bool hashTable::remove(const std::string &key){
  int pos;
  if((pos = findPos(key)) != -1){
    data[pos].isDeleted = true;
    return true;
  }
  return false;
}

int hashTable::hash(const std::string &key){
  //Referred to djb2 Hash Algorithm
  int hash = 5381;
  const char *c = key.c_str();

  while (*c++){
    hash = ((hash << 5) + hash) + (int)*c;
  }
  return true;
}

int hashTable::findPos(const std::string &key){
  int pos = hash(key) % capacity;
  int pos1 = pos;
  int pos2 = 0;

  while(pos1 < capacity && data[pos1].isOccupied && data[pos1].key.compare(key)){
    pos1++;
  }
  if(pos1 == capacity){
    while(data[pos].isOccupied && data[pos2].key.compare(key)){
      pos2++;
    }
  }

  if(pos1 < capacity && data[pos1].isOccupied && !data[pos1].key.compare(key) && !data[pos1].isDeleted){
    return pos1;
  }
	else if(data[pos].isOccupied && !data[pos2].key.compare(key) && !data[pos2].isDeleted){
    return pos2;
  }
	else{
    return -1;
  }
}

bool hashTable::rehash(){
  vector<hashItem> tmp = data;
  int oldCapacity = this->capacity;
  //Reset HashTable
  for(int i = 0; i < capacity; i++){
    data[i].isOccupied = false;
    data[i].isDeleted = true;
  }

  capacity = getPrime(capacity * 2);
  data.resize(capacity);
  if(data.size() != capacity){
    return false;
  }
  //Empty HashTable
  filled = 0;
  //Reinsert Data Values
  for(int i = 0; i < oldCapacity; i++){
    if(!tmp[i].isDeleted && tmp[i].isOccupied){
      insert(tmp[i].key, tmp[i].pv);
    }
  }
  vector<hashItem>().swap(tmp);
  return true;

}

unsigned int hashTable::getPrime(int size){
    unsigned int prime[] = {1543, 3079, 6151, 12289, 24593, 49157, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319};
    int num = 0;

    while(prime[num] < size){
      num++;
    }
    // DEBUGGING: cout << prime[num];
    return prime[num];
}
