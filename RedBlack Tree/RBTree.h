#ifndef RB_tree_H
#include "RBNode.h"
#include <stdio.h>
#include <iostream>

template <typename K, typename V> class RBTree
{
public:
	//constructor & destructor
	RBTree();
	~RBTree();

	//RBT insert functions
	void insert(K key, V value);	//inserting a new node into the tree

	//RBT Delete Functions
	void remove(K key);

	//finds a node in the tree
	RBNode<K, V>* findNode(K key);

	int getSize(){ return this->size; };
	V getValue(K key);


private:

	RBNode<K, V>* R;	//root
	int size;			//size of the tree
	RBNode<K, V>* NIL;	//non-existent leaf/parent node


	//Insert Functions
	void InsertFixUp(RBNode<K, V>* Z);
	void LRotate(RBNode<K, V>* X);
	void RRotate(RBNode<K, V>* X);


	//RBT deleting functions
	void CascadeDelete(RBNode<K, V> * X);
	void NodeDel(RBNode<K, V> * Z);
	void RBTransplant(RBNode<K, V> * Z, RBNode<K, V> * X);
	void TMin(RBNode<K, V> * Z);
	void DelFixUp(RBNode<K, V> * X);


	
};

//tree constructor 
template <typename K, typename V> RBTree<K,V>::RBTree()
{
	//setting the size of the tree to 0
	this->size = 0;

	//creating the NIL and setting the root to it 
	this->NIL = new RBNode<K, V>();
	this->R = this->NIL;
}

//Destructor 
template <typename K, typename V> RBTree<K, V>::~RBTree()
{
	if (this->R != this->NIL)
	{
		this->CascadeDelete(this->R);
	}
	delete this->NIL;

}

template <typename K, typename V> void RBTree<K, V>::insert(K key, V value){

	RBNode<K, V>* Y = this->NIL;
	RBNode<K, V>* X = this->R;
	RBNode<K, V>* Z = new RBNode<K, V>(key, value);

	//finding the closest key to the key of z
	while (X != this->NIL)
	{
		Y = X;

		if (key < X->getK())
		{
			X = X->getL();
		}
		else
		{
			X = X->getR();
		}
	}

	//setting the parent of z to the node that y is pointing to
	Z->setP(Y);

	
	if (Y == this->NIL)
	{
		this->R = Z;
	}
	else
	{
		if (Z->getK() < Y->getK())
		{
			Y->setL(Z);
		}
		else
		{
			Y->setR(Z);
		}
	}

	Z->setL(this->NIL);
	Z->setR(this->NIL);
	this->InsertFixUp(Z);
	this->size++;
}

//creates a new node and adds it to the tree
template <typename K, typename V> void RBTree<K, V>::InsertFixUp(RBNode<K, V>* Z){
	RBNode<K, V>* Y;

	while (Z->getP()->getColour())
	{
		if (Z->getP() == Z->getP()->getP()->getL())
		{
			Y = Z->getP()->getP()->getR();
			
			if ( Y->getColour())
			{
				Z->getP()->setColour(false);
				Y->setColour(false);
				Z->getP()->getP()->setColour(true);
				Z = Z->getP()->getP();
			}
			else
			{
				if (Z == Z->getP()->getR())
				{
					Z = Z->getP();
					LRotate(Z);
				}

				Z->getP()->setColour(false);
				Z->getP()->getP()->setColour(true);
				RRotate(Z->getP()->getP());
			}
		}
		else
		{
			Y = Z->getP()->getP()->getL();
			if (Y->getColour())
			{
				Z->getP()->setColour(false);
				Y->setColour(false);
				Z->getP()->getP()->setColour(true);
				Z = Z->getP()->getP();
			}
			else
			{
				if (Z == Z->getP()->getL())
				{
					Z = Z->getP();
					RRotate(Z);
				}
				Z->getP()->setColour(false);
				Z->getP()->getP()->setColour(true);
				LRotate(Z->getP()->getP());
			}
		}
	}

	this->R->setColour(false);
}


//rotates a subtree left
template <typename K, typename V> void RBTree<K, V>::LRotate(RBNode<K, V>* X){
	RBNode<K, V>* Y = X->getR();
	X->setR(Y->getL());

	if (Y->getL() != this->NIL)
	{
		Y->getL()->setP(X);
	}

	Y->setP(X->getP());

	if (X->getP() == this->NIL)
	{
		this->R = Y;
	}
	else if (X == X->getP()->getL())
	{
			X->getP()->setL(Y);
	}
	else
	{
		X->getP()->setR(Y);
	}

	Y->setL(X);
	X->setP(Y);

}

//rotates a subtree Right
template <typename K, typename V> void RBTree<K, V>::RRotate(RBNode<K, V>* X){
	RBNode<K, V>* Y = X->getL();
	X->setL(Y->getR());

	if (Y->getR() != this->NIL)
	{
		Y->getR()->setP(X);
	}

	Y->setP(X->getP());

	if (X->getP() == this->NIL)
	{
		this->R = Y;
	}
	else if (X == X->getP()->getR())
	{
		X->getP()->setR(Y);
	}
	else
	{
		X->getP()->setL(Y);
	}

	Y->setR(X);
	X->setP(Y);

}

//Function to delete a node and all the nodes it references
template <typename K, typename V> void RBTree<K, V>::CascadeDelete(RBNode<K, V> * X){
	if (X != this->NIL)
	{
		this->CascadeDelete(X->getL());
		this->CascadeDelete(X->getR());
		delete X;
	}

}


//finds a node in the tree
template <typename K, typename V> RBNode<K, V>* RBTree<K, V>::findNode(K key){
	RBNode<K, V>* Y = this->R;

	while (Y != this->NIL)
	{
		if (key == Y->getK())
		{
			return Y;
		}
		else if (key < Y->getK())
		{
			Y = Y->getL();
		}
		else
		{
			Y = Y->getR();
		}

	}

	return Y;

}

//removes a node from the tree
template <typename K, typename V> void RBTree<K, V>::remove(K key){
	RBNode<K, V>* Y = this->findNode(key);

	if (Y != this->NIL)
	{
		this->NodeDel(Y);
		this->size--;
	}

}

template <typename K, typename V> void RBTree<K, V>::NodeDel(RBNode<K, V> * Z){
	RBNode<K, V>* Y = Z;
	RBNode<K, V>* X;
	bool OColour = Y->getColour();

	if (Z->getL() == this->NIL)
	{
		X = Z->getR();
		this->RBTransplant(Z, Z->getR);
	}
	else if (Z->getR() == this->NIL)
	{
		X = Z->getL();
		this->RBTransplant(Z, Z->getL);
	}
	else
	{
		Y = this->TMin(Z->getR);
		OColour = Y->getColour();
		X = Y->getR();
		if (Y->getP == Z)
		{
			X->setP(Y);
		}
		else
		{
			this->RBTransplant(Y, Y->getR());
			Y->setR(Z->getR());
			Y->getR()->setP(Y);
		}
		this->RBTransplant(Z,Y);
		Y->setL(Z->getL());
		Y->getL()->setP(Y);
		Y->setColour(Z->getColour());
	}
	if (OColour == false)
	{
		this->DelFixUp(X);
	}
}

template <typename K, typename V> void RBTree<K, V>::RBTransplant(RBNode<K, V> * Z, RBNode<K, V> * X){
	if (Z->getP() == this->NIL)
	{
		this->R = X;
	}
	else if (Z == Z->getP()->getL())
	{
		Z->getP()->setL(X);
	}
	else
	{
		Z->getP()->setR(X);
	}
	X->setP(Z->getP());
}

template <typename K, typename V> void RBTree<K, V>::TMin(RBNode<K, V> * Z){
	while (Z->getL() != this->NIL)
	{
		Z = Z->getL();
	}
	return Z;
}
template <typename K, typename V> void RBTree<K, V>::DelFixUp(RBNode<K, V> * X){
	RBNode<K, V>* W;
	while (X != this->R && X->getColour == false)
	{
		if (X == X->getP()->getR())
		{
			W = X->getP()->getR();
			if (W->getColour() == true)
			{
				W->setColour(false);
				X->getP()->setColour(true);
				this->LRotate(X->getP());
				W = X->getP()->getR();
			}

			if (W->getL()->getColour() == false && W->getR()->getColour() == false)
			{
				W->setColour(true);
				X = X->getP();
			}
			else if (W->getR()->getColour() == false)
			{
				W->getL()->setColour(false);
				W->setColour(true);
				this->RRotate(W);
				W = X->getP()->getR();
			}

			W->setColour(X->getP()->getColour());
			X->getP()->setColour(false);
			W->getR()->setColour(false);
			this->LRotate(X->getP());
			X = this->R;

		}
		else
		{
			W = X->getP()->getL();
			if (W->getColour() == true)
			{
				W->setColour(false);
				X->getP()->setColour(true);
				this->rRotate(X->getP());
				W = X->getP()->getl();
			}

			if (W->getR()->getColour() == false && W->getL()->getColour() == false)
			{
				W->setColour(true);
				X = X->getP();
			}
			else if (W->getL()->getColour() == false)
			{
				W->getR()->setColour(false);
				W->setColour(true);
				this->LRotate(W);
				W = X->getP()->getL();
			}

			W->setColour(X->getP()->getColour());
			X->getP()->setColour(false);
			W->getL()->setColour(false);
			this->RRotate(X->getP());
			X = this->R;
		}
	}
}

template <typename K, typename V> V RBTree<K, V> ::getValue(K key){
	RBNode<K, V>* W = this->findNode(key);
	return W->getV();
}



#endif
