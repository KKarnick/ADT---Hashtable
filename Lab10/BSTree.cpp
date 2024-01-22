
#include "BSTree.h"

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;  //given
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other ){
	if (this != &other) {
		clear();
		copyHelper(root, other.root);  //call private function
	}
	return *this;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other ){
	if (this != &other) {  //ensure not already same hash table
		clear();
		copyHelper(root, other.root);  //call private function
	}
	return *this;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree (){
	clear();  //clear out tree to null
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem ){
	insertHelper(newDataItem, root);  //call protected function
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const{
	        //call & return value from protected function
	if (retrieveHelper(searchKey, searchDataItem, root) == true)
		return true;
	else
		return false;
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey ){
	   //call protected function
	return removeHelper(deleteKey, root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const{
	//call protected function
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear (){
	//call protected function
	clearHelper(root);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const{
	if (root == nullptr)
		return true;
	else
		return false;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const{
	return heightHelper(root, 0);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const{
	  //call protected function
	return getCountHelper(root);

}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const{
	writeLessThanHelper(searchKey, root);
}


#include "show9.cpp"

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode* r, BSTreeNode* o) {
	if (other != nullptr) { //if root is null, no copy made
		   //set children
		BSTreeNode* left = nullptr;
		BSTreeNode* right = nullptr;
		   //recursively call copy through structure
		copyHelper(left, other->left);
		copyHelper(right, other->right);
		    //once leaf reached, set its val's & start returning values to each node
		r = new BSTreeNode(other->dataItem, left, right);
	}

}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insertHelper(const DataType& newDataItem, BSTreeNode* r) {

	if (r == nullptr)  //empty tree or leaf position (base case)
		r = new BSTreeNode(newDataItem, nullptr, nullptr);
	else {
		     //find appropriate location in tree
		if (newDataItem.getKey() < (r->dataItem).getKey())
			insertHelper(newDataItem, r->left);
		else if (newDataItem.getKey() > (r->dataItem).getKey())
			insertHelper(newDataItem, r->right);
		else  //same location, so update data
			(r->dataItem).getKey() = newDataItem.getKey();
	}
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(const KeyType& searchKey, DataType& searchDataItem, BSTreeNode* r) const{

	if (r != nullptr) {  //if root is null, no match
		//check searchKey vs. each node's data
		if (searchKey == (r->dataItem).getKey()) {
			searchDataItem = r->dataItem;   //set searchItem with retrieved data
			return true;
		}
		else if (searchKey < (r->dataItem).getKey())  //if key is less than root data, search left child
			return retrieveHelper(searchKey, searchDataItem, r->left);
		else  //it's greater, so search right child
			return retrieveHelper(searchKey, searchDataItem, r->right);
	}
	else
		return false;  //if null has been reached and no match found, return false
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(const KeyType& deleteKey, BSTreeNode * &r){
	if (r != nullptr) { //no data exists at location

		if (deleteKey == (r->dataItem).getKey()) {
			//determine children
			//case 1: leaf
			if ((r->right == nullptr) && (r->left == nullptr)) {
				delete r;
				r = nullptr;
			}
			//case2: one child
			else if (r->left == nullptr) {
				BSTreeNode* curr = r;
				r = r->right;
				delete curr;
			}
			else if (r->right == nullptr) {
				BSTreeNode* curr = r;
				r = r->left;
				delete curr;
			}
			//case 3: 2 children
			else {
				BSTreeNode* curr = r->right;
				//find least value (leftmost) of greater subtree
				while (curr->left != nullptr)
					curr = curr->left;
				r->dataItem = curr->dataItem;  //set least value to r
				return removeHelper((curr->dataItem).getKey(), r->right);
			}
			return true;
		}
		//if deleteKey not found, search appropriate subtree
		else if (deleteKey < (r->dataItem).getKey())
			return removeHelper(deleteKey, r->left);
		else  //must be greater
			return removeHelper(deleteKey, r->right);
	}
	else
		return false;
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* r) const {
	if (r != nullptr) {
		writeKeysHelper(r->left);
		cout << (r->dataItem).getKey() << "  ";
		writeKeysHelper(r->right);
	}
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode* r) {
	if (r != nullptr) {  //not empty tree
		clearHelper(r->left);
		clearHelper(r->right);
		delete r;
		r = nullptr;
	}
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::heightHelper(BSTreeNode* r, int level) const{
	int highestLevel = 0;  //current highest level traversed
	if (r == nullptr) {
		if (level > highestLevel)
			highestLevel = level;
	}
	else {
		heightHelper(r->left, level + 1); //call again and add current level 
		heightHelper(r->right, level + 1);
	}
	return highestLevel;

}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::countHelper(BSTreeNode* r) const {
	if (r == nullptr)  //if node is null, add 0 to count
		return 0;
	else
		return (1 + countHelper(r->left) + countHelper(r->right));  //add "self" to subtree counts
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThanHelper(const KeyType& searchKey, BSTreeNode* r) const {
	if (r != nullptr) {
		writeLessThanHelper(searchKey, r->left);
		if ((r->dataItem).getKey() < searchKey)
			cout << (r->dataItem).getKey() << "  ";
		writeLessThanHelper(searchKey, r->right);
	}
}