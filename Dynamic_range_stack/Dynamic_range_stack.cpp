/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  jm3zhang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
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

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ): 
entry_count( 0 ),  // the entry counter for the Main stack
min_count( 0 ),	 // the entry counter for the Min stack
max_count( 0 ),	 // the entry counter for the max stack
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	
	// empty constructor

}

Dynamic_range_stack::~Dynamic_range_stack() {
	// Enter your implementation here.
	//	There are 3 arrays stack_array, maximum_array, minimum_array

	if (stack_array){  // check if the array exists
		delete[] stack_array;
	}
	if (maximum_array){  // check if the array exists
		delete[] maximum_array;
	}
	if (minimum_array){  // check if the array exists
		delete[] minimum_array;
	}

} //Done

//if there are 10 items in it, the counter is 10, the index is 9
int Dynamic_range_stack::top() const {
	// Enter your implementation here.
	/*Algorithm top()
	if isEmpty() then
		return Error 
	return S[t]*/

	// need to finish Done
	
	try{
		if(empty()){
			throw underflow();
		}
	}
	catch(int a){

	}
   	
	return stack_array[entry_count - 1];
}//Done

int Dynamic_range_stack::maximum() const {
	// Enter your implementation here.
	// sort the stack array into the maximum array, B ---> S, Return the first value of the Maximum array

	return maximum_array[max_count - 1];
}//Done

int Dynamic_range_stack::minimum() const {
	// Enter your implementation here.
	// sort the stack array into the maximum array, S ---> B, Return the first value of the Maximum array

	return minimum_array[min_count - 1];
}//Done

int Dynamic_range_stack::size() const {
	// Enter your implementation here.
	/*Algorithm size() 	
		return t+1*/

	return entry_count;
}//Done

bool Dynamic_range_stack::empty() const {
	// Enter your implementation here.
	/*Algorithm isEmpty() 
		return (t<0)*/

	return (entry_count <= 0);
} //Done

int Dynamic_range_stack::capacity() const {
	// Enter your implementation here.
	// Return the current capacity of the arrays in (𝑂(1))

	return current_capacity;
}//Done



void Dynamic_range_stack::push( int const &obj ) {
	// Enter your implementation here.
	/*Algorithm push(o) 
		if size()==N then
			return Error 
		t=t+1
		S[t]=o*/
	//need to consdie if the stack it 


	if(empty()){
		stack_array[entry_count] = obj;
		maximum_array[max_count] = obj;
		minimum_array[min_count] = obj;
		entry_count ++;
		max_count ++;
		min_count ++;
		return;
	}

	if(entry_count == current_capacity){
		int * stack_temp = new int[entry_count];
		int * max_temp = new int[entry_count];
		int * min_temp = new int[entry_count];

		//if there are 10 items in it, the counter is 10, the index is 9
		for(int a; a<entry_count; a++){
			stack_temp[a] = stack_array[a]; 
			max_temp[a] = maximum_array[a];
			min_temp[a] = minimum_array[a];
		}
			

		delete[] stack_array;
		delete[] maximum_array;
		delete[] minimum_array;

		current_capacity *= 2;
		stack_array = new int[current_capacity]; 
		maximum_array = new int[current_capacity]; 
		minimum_array = new int[current_capacity]; 

		 //if there are 10 items in it, the counter is 10, the index is 9

		for(int a=0; a<entry_count; a++){
			stack_array[a] = stack_temp[a];
			maximum_array[a] = max_temp[a];
			minimum_array[a] = min_temp[a];
		}

		delete[] stack_temp;
		delete[] max_temp;
		delete[] min_temp;
	}
	
	if(obj > maximum_array[max_count - 1]){
		maximum_array[max_count] = obj;
		max_count ++; //2 more than the actually stack counter
	}
	
	if(obj < minimum_array[min_count - 1]){
		minimum_array[min_count] = obj;
		min_count ++; //2 more than the actually stack counter
	}
	
	stack_array[entry_count] = obj;
	entry_count ++; //2 more than the actually stack counter
	
	return;

}//Done

int Dynamic_range_stack::pop() {
	//std::cout<<"stack array: "<<*(stack_array+entry_count)<<std::endl;
	// Enter your implementation here.
	/*Algorithm pop() 
		if isEmpty() then
			return Error S[t]=null
		t=t-1*/
	try{
		if(empty()){
			throw underflow();
		}
	}
	catch(int a){

	}

   	// When the counter decreased, the array is poped tho the index is still there, However it will be overwitten by next push
	if(stack_array[entry_count - 1] == maximum_array[max_count - 1]){ 
		max_count --;
	}
	
	if(stack_array[entry_count - 1] == minimum_array[min_count - 1]){
		min_count --; //2 more than the actually stack counter
	}

	entry_count --;
	
	return stack_array[entry_count];
}//Done

void Dynamic_range_stack::clear() {
	// Enter your implementation here.
	//empty the arrays
	//if(current_capacity > initial_capacity){
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;

	current_capacity = initial_capacity;
	stack_array = new int[current_capacity]; 
	maximum_array = new int[current_capacity]; 
	minimum_array = new int[current_capacity]; 
	//}

	entry_count = 0;
	max_count = 0;
	min_count = 0;

}//Done

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif