
#include "HashTable.h"

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize){
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other){
	tableSize = other.tableSize;  //init size 0
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	      //copy values
	copyTable(other);
}

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other){
	if (this != &other) {  //ensure not same table
		clear();
		if (!other.isEmpty())  //if other is empty, done; else, copy other
			copyTable(other);
	}
	return *this;  //return this in either case
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable(){
	clear();  //delete tree at each location if it exists
	 //then reset variables
	tableSize = 0;
	dataTable = nullptr;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem){
	unsigned int loc = DataType::hash(newDataItem.getKey()) % tableSize;
	dataTable[loc].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey){
	unsigned int loc = DataType::hash(deleteKey) % tableSize;
	if (dataTable[loc].remove(deleteKey))
		return true;
	else
		return false;
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const{
	unsigned int loc = DataType::hash(searchKey) % tableSize;
	if(dataTable[loc].retrieve(searchKey, returnItem))
		return true;
	else
		return false;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear(){
	for (int i = 0; i < tableSize; i++)
		dataTable[i].clear();
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const{
	for (int i = 0; i < tableSize; i++) {
		if(!(dataTable[i].isEmpty()) )  //if any location is not empty, return false immediately
			return false;
	}
	return true;  //if false not found, true is case
}

#include "show10.cpp"

template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{
}
