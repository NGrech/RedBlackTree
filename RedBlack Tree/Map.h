#ifndef MAP_H


#include "RBTree.h"
template<typename K, typename V> class Map
{
public:

	Map();
	~Map();

	void put(K key, V value);
	V get(K key);
	void remove(K key);
	int getSize();

private:

	RBTree<K, V>* T;
};


template<typename K, typename V> Map<K, V> ::Map(){
	this->T = new RBTree<K, V>();
}

template<typename K, typename V> Map<K, V> ::~Map(){
	delete this->T;
}

template<typename K, typename V> void Map<K, V> ::put(K key, V value){
	this->T->insert(key, value);
}

template<typename K, typename V> V Map<K, V> ::get(K key){
	return this->T->findNode(key);
}

template<typename K, typename V> void Map<K, V> ::remove(K key){
	this->T->remove(key);
}

template<typename K, typename V> int Map<K, V> ::getSize(){
	return this->T->getSize();
}



#endif
