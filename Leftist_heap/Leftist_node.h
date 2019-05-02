/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

// You must implement everything
//Accessors
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return element;
}// done

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
	return left_tree;
} //done

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
	return right_tree;
}//done

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (this == nullptr){
		return -1;
	}
	return heap_null_path_length;
}	// done

template <typename Type>
	int Leftist_node<Type>::count( const Type &obj ) const {
		//sine this function is called in the heap clasee with the root_node, just do an left walk and a right walk wrt the root
		//to get the number of obj
		//start from the root:
		//static_cast<int>(obj);
		/*if (root_node == nullptr) { 
			return 0; 
		}
		if (		) {    
			return 1;  
		}
		leftNodeNumber =NumberOfNodesAtALevel (left(n), 1 – 1);
		rightNodeNumber = NumberOfNodesAtALevel (light(n), 1 – 1);
		totalNode = leftNodeNumber + rightNodeNumber;
		return totalNode;*/

		int counter = 0;
		int leftNodeNumber;
		int rightNodeNumber;

		if (this == nullptr) {
			return 0;
		}
		if (element == obj) {
			counter ++;
		}
		//else counter = 0;

		counter = counter + left() -> count(obj);
		counter = counter + right() -> count(obj);
		
		return counter;
	}	

//Mutators
template<typename Type >
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
	// enter your implemetation here
	//static_cast<int>
	//If the new heap is null, return.
	if (new_heap == nullptr/*!!!!!!*/){
		return;
	}
	//first case
	//i) if this is null, set the pointer to this to be the new heap and return
	if (this == nullptr){
		ptr_to_this = new_heap;
		return;
	}

	//second case
	//ii) if the current node is storing a value less-than-or- equal-to the value stored 
	//in the root of the new heap, push the new node onto the right sub-tree with right_tree. 
	//Now, update the null-path length and if the left-sub-tree has a smaller null-path 
	//length than the right sub-tree, swap the two sub-trees
	else if (ptr_to_this -> retrieve() <= new_heap ->retrieve()){
		right_tree -> push(new_heap, right_tree);
		// update the null-path length 
		if(left_tree -> null_path_length() < right_tree -> null_path_length()){ // swap
			heap_null_path_length = left_tree -> null_path_length() + 1;  
			std::swap(left_tree, right_tree);
		}
		else{ //no swap
			heap_null_path_length = right_tree -> null_path_length() + 1;  
		}

	}

	//third case
	//iii) otherwise, set the pointer to this to be the new heap and push this node into t
	//he new heap (with an appropriate second argument)
	else{
		ptr_to_this = new_heap;
		ptr_to_this -> push (this, ptr_to_this);
	}

	return;
}

template<typename Type >
void Leftist_node<Type>::clear() {
	// enter your implemetation here
	//static_cast<int>
	if (this == nullptr){
		return;
	}
 	this -> left_tree -> clear();
 	this -> right_tree -> clear(); 
 	delete this;

	return;
} // done


#endif