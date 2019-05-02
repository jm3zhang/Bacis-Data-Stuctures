#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  jm3zhang
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function
		int doubleH( int const  , int const ) const;

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), // The number of elements currently in the hash table
power( m ), // 2^m, part of the capacity of the table
array_size( 1 << power ),   // The capacity of the hash table
array( new T [array_size] ),  // Hash table already created
array_state( new state[array_size] ) {   // The state of the bin (EMPTY OCCUPIED DELETED) already created
	//2 arrays, one for actually value (array), one for state (array_state)

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

/*Destructor*/
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// enter your implemetation here 
	if (array){  // check if the array exists
		delete[] array;
	}
	if (array_state){  // check if the array exists
		delete[] array_state;
	}
}

/*Accessors*/
template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implemetation here 
	return count;
} //Done

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implemetation here 
	return array_size;
} //Done 

template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implemetation here 
    // return (count <= 0);
    if (count <= 0){
		return true;
	}
	else{
		return false;
	}
} //Done

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// enter your implemetation here 
	/*In this project, h1(𝑘) first statically casts the input to an int (see documentation for static_cast<int>), 
	then takes this integer module M (i.e. 𝑘%𝑀) and finally adding M if the value is negative. */
	int theObject = static_cast<int>(obj);

	int index1;
	index1 = theObject % array_size;
	if (index1 < 0){				// check if negative
		index1 += array_size;
	}

	return index1;
} //Done

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// enter your implemetation here 
	/*The hash function h2(𝑘), (that determines the offset) is derived from the integer divided by M module M,
	((𝑘/ 𝑀)%𝑀). This value is again made positive, if necessary, by adding M. Add 1 if the resulting value is 
	even in order to make it odd.*/
	int theObject = static_cast<int>(obj);

	int index2;
	index2 = (theObject/array_size) % array_size;
	if (index2 < 0){				// check if negative
		index2 += array_size;
	}
	if (index2 % 2 == 0){			// check if even
		index2 += 1;
	}

	return index2;
} //Done
/*
template<typename T >
int DoubleHashTable<T >::doubleH( int const v , int const i) const {

	// static_cast<int>(obj);

	int index3;
	int hash1;
	int hash2;

	hash1 = h1(v);
	hash2 = h2(v);

	index3 = (hash1 + (i * hash2)) % array_size;

	return index3;
} //Done*/

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// enter your implemetation here 
	// h(𝑘, 𝑖) = (h1(𝑘) + 𝑖h2(𝑘)) 𝑚𝑜𝑑 𝑀
	//int theObject = static_cast<int>(obj);


	int hash1;
	int hash2;
	int index3;

	hash1 = h1(obj);
	hash2 = h2(obj);

	for (int i = 0; i < array_size /*!!!!!*/; ++i){
		index3 = (hash1 + (i * hash2)) % array_size;
		if (array_state[index3] == EMPTY){
			break;
		}
		if (array[index3] == obj && array_state[index3] == OCCUPIED){
			return true;
		}
	}

	return false;
} // Done

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {

    // enter your implemetation here 	      
	if (array_state[n] == OCCUPIED){
		return array[n];
	}
	return 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here 	

	/*for (int i = 0; i < array_size ; ++i){
		std::cout << array[i] << " " << array_state[i] << std::endl;
	}

	std::cout << count << " " << array_size << std::endl;
	return;*/
}

/*Mutators*/
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	// enter your implemetation here
	//int theObject = static_cast<int>(obj);

	try{
		if(count == array_size){
			throw overflow();
		}
	}
	catch(int a){

	}

	int hash1;
	int hash2;
	int index3;

	hash1 = h1(obj);
	hash2 = h2(obj);

	for (int i = 0; i < array_size /*!!!!!*/; i++){
		index3 = (hash1 + (i * hash2)) % array_size;
		if (array_state[index3] == EMPTY || array_state[index3] == DELETED){
			array[index3] = obj;
			array_state[index3] = OCCUPIED;
			count ++;
			break;
		}
	}

	return; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	// enter your implemetation here 
	//int theObject = static_cast<int>(obj);

	if(member(obj)){

		int hash1;
		int hash2;
		int index3;

		hash1 = h1(obj);
		hash2 = h2(obj);

		for (int i = 0; i < array_size /*!!!!!*/; ++i){
			index3 = (hash1 + (i * hash2)) % array_size;
			if (array[index3] == obj && array_state[index3] == OCCUPIED){
				array_state[index3] = DELETED;

			}
		}
		count --;
		return true;
	}

	return false;
} 

template<typename T >
void DoubleHashTable<T >::clear() {
	 // enter your implemetation here 
	for (int i = 0; i < array_size; i++){
		//array_state[i] = 0;
		array_state[i] = EMPTY;
 	}
 	count = 0;

	return ; 
} //Done

#endif