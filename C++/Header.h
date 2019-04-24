// FILE: sequence2.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_4)
// There is no implementation file provided for this class since it is
// an exercise from Chapter 4 of "Data Structures and Other Objects Using C++"
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   static const int DEFAULT_CAPACITY = _____
//     sequence::DEFAULT_CAPACITY is the initial capacity of a sequence that is
//     created by the default constructor.
//
// CONSTRUCTORS for the sequence class:
//   sequence(int initial_capacity = DEFAULT_CAPACITY)
//     Postcondition: The sequence has been initialized as an empty sequence.
//     The insert/attach functions will work efficiently (without allocating
//     new memory) until this capacity is reached.
//
//   sequence(const sequence& source)
//     Postcondition: the sequence has made a deep copy of the source sequence.
//
//  DESTRUCTOR:
//	 ~sequence()
//		Poscondition: all dynamically allocated memory has been destroyed.
//
//	OPERATOR:
//	  void operator =(const sequence& source);
//	  Postondition: a deep copy of the source sequence replaces the current sequence.
//                  Unused dynamic memory is deallocated.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void resize(int new_capacity)
//     Postcondition: The sequence's current capacity is changed to the 
//     new_capacity (but not less that the number of items already on the
//     list). The insert/attach functions will work efficiently (without
//     allocating new memory) until this new capacity is reached.
//
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
//	   else there is no current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   int size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
//Benchmarks*********************************
//hello world********************************
//learn about a sequence******************************8
//member function implementation
//resize *******************************************8
//start ************************************************
//advance *********************************************
//insert ********************************************
//attach *****************************
//remove current
//constant
//size ***********************************************888888
//is_item ************************************************
//current *************************************************
//operator overload implementation
//default constructor implementation************************
//copy ********************************************8
//destructor *****************************************88
#include <iostream>
using namespace std;

#ifndef MAIN_SAVITCH_SEQUENCE_H
#define MAIN_SAVITCH_SEQUENCE_H


namespace main_savitch_4
{
	//typedef double value_type;

	class sequence
	{
	public:
		// TYPEDEFS and MEMBER CONSTANTS

		static const int DEFAULT_CAPACITY = 5;
		// CONSTRUCTORS and DESTRUCTOR
		sequence(int initial_capacity = DEFAULT_CAPACITY)
		{
			//initialize sequence array to the data pointer
			data = new double[initial_capacity];
			//set capacity to default capacity 
			capacity = DEFAULT_CAPACITY;
			used = 0;
		}
		sequence(const sequence& source)
		{
			data = new double[source.capacity];
			capacity = source.capacity;
			used = source.used;
			for (int i = 0; i < used; i++)
			{
				data[i] = source.data[i];
			}
		}
		~sequence()
		{
			delete[] data;
		}
		// MODIFICATION MEMBER FUNCTIONS
		void resize(int new_capacity)
		{
			double *larger_array;
			// check to see if the current capacity is the old one 
			if (capacity == new_capacity)
				return;
			//check to see if the new capacity is less than whats being used 
			if (new_capacity < used)
				new_capacity = used;

			larger_array = new double[new_capacity]; //initialize larger array as a dynamically allocated array 
			for (int i = 0; i <= used; i++)
			{
				larger_array[i] = data[i];
			}//copy data array to larger array 
			delete[] data; // delete data 
			data = larger_array; // set data to larger array 
			capacity = new_capacity;

		}
		void start()
		{
			if (used == 0)
				current_index = -1; //shows that sequence is empty 
			else
				current_index = 0;
		}
		void advance()
		{
			if (is_item() == false)
				return;
			else if (current_index + 1 == used)
				current_index = -1;
			else
				current_index++;
		}
		void insert(const double& entry)
		{
			//take entry and input it into the current location then slide the other data down 
			if (used >= capacity) // see if there is room 
				resize(used);
			double current_holder = data[current_index]; //save value at current index 
			data[current_index] = entry;  //set passed value at current index 
											  // slide all the data down 
			for (int i = 0; i < (used - current_index); i++)
			{
				data[used - i] = data[used - 1 - i];//slide each value from the end down one 
			}
			data[current_index + 1] = current_holder;//put the holder in the remaining spots. 
			used++;
			
		}
		void attach(const double& entry)
		{
			if (current_index < 0)
			{
				current_index = 0;
				data[current_index] = entry;
				used = 1;
			}
			else if (current_index >= 0)
			{
				current_index++;
				double holder = data[current_index];
				data[current_index] = entry;
				for (int i = 0; i < (used - current_index); i++)
				{
					data[used - i] = data[used - 1 - i];
				} 
				data[current_index + 1] = holder;
				used++;
			}
		}
		void remove_current()
		{
			if (is_item() == false)
				return;
			if (current_index < 0)
				return;
			if (used - 1 == current_index) // last item in the sequence 
			{
				data[current_index] = NULL;
				current_index--;
				used--;
			}
			else
			{
				for (int i = 0; i < (used - current_index); i++)
				{
					data[current_index + i] = data[current_index + 1 + i];
				}
				used--;
			}

		}
		void operator =(const sequence& source)
		{
			double* temp_array = new double[source.capacity];
			for (int i = 0; i < source.used; i++)//copy B to A
			{
				temp_array[i] = source.data[i];
			}
			data = temp_array;
			used = source.used;
			capacity = source.capacity;
		}
		// CONSTANT MEMBER FUNCTIONS
		int size() const
		{
			return used;
		}
		bool is_item() const
		{
			if (current_index < 0)
				return false;
			else if (current_index >= used)
				return false;
			else
				return true;
		}
		double current() const
		{
			if (is_item() == false)
				return 0;
			return data[current_index ];
		}
	private:
		double* data;
		int used;
		int current_index;
		int capacity;
	};
}

#endif

