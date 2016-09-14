#ifndef RB_node_H
#define RB_node_H

template<typename K, typename V> class RBNode
{
private:
	RBNode<K, V> *L;	//left child
	RBNode<K, V> *R;	//right child
	RBNode<K, V> *P;	//parent
	bool Colour;		//colour of node Note red = true & black = false
	K key;				//key of node
	V value;			//value of node

public:

	//constructors and destructor 
	RBNode();
	RBNode(K key, V value);

	~RBNode();

	//getters and setters for Parent, Left and Right children
	RBNode<K, V> *getL(){ return this->L; }
	void setL(RBNode<K, V> *L){ this->L = L; }
	RBNode<K, V> *getR(){ return this->R; }
	void setR(RBNode<K, V> *R){ this->R = R; }
	RBNode<K, V> *getP(){ return this->P; }
	void setP(RBNode<K, V> *P){ this->P = P; }

	//getter and setter for colour
	bool getColour(){ return this->Colour; }
	void setColour(bool C) { this->Colour = C; }

	//getter for key
	K getK(){ return this->key; }

	//getter and setter for value
	V getV(){ return this->value; }
	void steV(V val){ this->value = val; }


	bool operator>(const RBNode<K, V>& node){
		return this->key > node.key;
	}

	bool operator<(const RBNode<K, V>& node){
		return this->key < node.key;
	}

	bool operator==(const RBNode<K, V>& node){
		return this->key == node.key;
	}


	
};

template<typename K, typename V> RBNode<K, V>::RBNode()
{
	//setting initial children and parent to 0
	this->L = 0;
	this->R = 0;
	this->P = 0;

	//setting initial colour to black for the root
	this->Colour = false;

	//setting the key and value to the ones passed
	this->key = key;
	this->value = value;

}

template<typename K, typename V> RBNode<K, V>::RBNode(K key, V value)
{
	//setting initial children and parent to 0
	this->L = 0;
	this->R = 0;
	this->P = 0;

	//setting initial colour to red
	this->Colour = true;

	//setting the key and value to the ones passed
	this->key = key;
	this->value = value;

}

template<typename K, typename V> RBNode<K, V>::~RBNode()
{
}
#endif