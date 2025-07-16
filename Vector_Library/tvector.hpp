#include <iostream>
#include <utility>


using namespace std;

template<class T>
TVector< T >::TVector(){// default constructor 


	// set variables to default
	capacity = SPARECAPACITY;
	size = 0;
	array = new T[capacity];
	array[size] = dummy;


}// default constructor

template<class T>
TVector<T>::TVector(T val, int num){//param constructor

 	// sets parameters 
	capacity = num + SPARECAPACITY;
	size = num;
	array = new T[capacity];

	//sets values to val
	for(int i =0; i < num; i++)
	array[i] = val;
}// param constructor


template<class T>
TVector<T>& TVector<T>::operator=(TVector<T> && v){ // move assignment operator

   //swaps variables 
   swap(capacity, v.capacity);
   swap(size, v.size);
   swap(array, v.array);

  // returns current object
  return *this;

} // move assignment operator


template<class T>
TVector< T >::~TVector(){      // destructor

   // deletes array
   delete [] array;

}                             // destructor 

template<class T>
TVector<T>::TVector(const TVector<T>& v){ // copy constructor 

   // copies variables
   capacity = v.capacity;
   size = v.size;
   array = new T[capacity];

     // copies values to current object array
   for(int i=0; i < size; i++)
	array[i] = v.array[i];

}// copy constructor 

template <class T> 
TVector<T>& TVector<T>::operator=(const TVector<T>& v){ // copy assignment operator 

  // checks if copying the same object to itself 
  if(this != &v)
	
  {
	
	//copies variables
   	capacity = v.capacity;
  	size = v.size;

	//clears array and makes new one with copied capacity
	delete[] array;
	array = new T[capacity];

	// copies array values 
	for(int i=0; i < size; i++)
		array[i] = v.array[i];


  }

  // returns current object  
  return *this;

}// copy assignment operator 

template <class T>
TVector<T>::TVector(TVector<T> && v){// move constructor

   // moves values to target object 
   size = v.size;
   capacity = v.capacity;
   array = v.array;

   // resets moved object's values to default 
   v.array = nullptr;
   v.size = 0;
   v.capacity =0;


}// move constructor


template <class T>
bool TVector<T>::IsEmpty() const { // IsEmpty

// checks boolean of size == 0
return size == 0;

}// IsEmpty 

template<class T>
void TVector<T>::Clear(){// clear

   // resets values to default and resets array to dummy 
   capacity = SPARECAPACITY;
   size = 0;
   delete[] array;
   array = new T[capacity];
   array[size] = dummy;

}// clear


template<class T>
int TVector<T>::GetSize() const {//GetSize

  return size; // returns size of vector 

}//GetSize

template <class T>
void TVector<T>::RemoveBack(){// RemoveBack


if(IsEmpty()== false)// if vector isnt empty removes back value 
size--; 

}// RemoveBack

template<class T>
T& TVector<T>::GetFirst() const {//GetFirst

   return array[0]; // returns value of first spot 

}//GetFirst

template<class T>
T& TVector<T>::GetLast() const {//GetLast


  return array[size - 1]; // returns value in last array spot 

}//GetLast

template<class T>
void TVector<T>::SetCapacity(unsigned int c){//SetCapacity

     // tests if c is less then size 
 if (c >= size)
  {

	// creates temp array to hold value
  	T* temp = new T[c];
  	for (int i = 0; i < size; i++)
  	temp[i]=array[i]; 
	
	//delete old array and set it to point to temp
  	delete [] array;
  	array = temp;   
  	capacity = c;
  } 
  
 else { // executes if C is smaller then size

 	// copys values up to C into temp 
 	T* temp = new T[c];
  	for (int i = 0; i < c; i++)
  	temp[i]=array[i]; 

 	// deltes array and sets it to point to temp
  	delete [] array;
  	array = temp;
  	size = c;
  	capacity = c;
   }

}//SetCapacity

template<class T>
void TVector<T>::InsertBack(const T& d){//InsertBack

 if (size == capacity){ // checks if vector has reached capacity

 	SetCapacity(capacity*2);  // doubles capacity

 }

     array[size++] = d; // increases size and sets new value to d

}//InsertBack


template<class T>
void TVector<T>::Print(std::ostream& os, char delim)const {//Print

	if(size == 0){ // checks if array is empty
		os<<"array is empty";
	}

	
	//prints array elements
	os<<array[0];  
	for (int i=1; i < size; i++)
	{
		os << delim << array[i];
	}

}//Print

template<class T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){// operatoor+
	
	TVector<T> res; // creates result array

 
        TVectorIterator<T> itr1 = t1.GetIterator(); // creater iterators for vectors
        TVectorIterator<T> itr2 = t2.GetIterator(); 

	// inserts iterator into vector and moves to next iterator 
	for(int i = 0; i < t1.GetSize(); ++i){
	
		res.InsertBack(itr1.GetData());
        	itr1.Next();	
	}
	
       
        // inserts iterator into vector and moves to next iterator
	for(int i = 0; i < t2.GetSize(); ++i){
		 res.InsertBack(itr2.GetData());      
        	itr2.Next();
        }

	return res; // returns result 
}// operator+

template<class T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d){//Insert

            
  if (IsEmpty()||pos.index >= size ){// checks if array is empty or pos is out of bounds 

	InsertBack(d); // inserts to back
	pos.index = size - 1;// sets iterator to new value
}

else {

	// checks if capacity is reached
 	if (size == capacity) 
   	SetCapacity(capacity *2);

         // sets vales to shifted values
 	for (int i = size; i > pos.index; i--) {
 	array[i] = array [i-1]; 
 }

 array[pos.index] = d; // inserts d 


 size++; // increments size 
 }

  // sets itr to new item 
 pos.ptr = &array[pos.index];
 pos.vsize = size;
 return pos;
}//insert

template<class T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos){//remove
	
         // checks if vector is empty or pos is out of bounds
	if(size == 0 || pos.index >= size || pos.index < 0)
	{
		TVectorIterator<T> itr;  // returns default irt
		return itr;
	}

	// runs through vector removing item
	TVectorIterator<T> ret_pos = pos;
	for(int i=pos.index ; i < size -1; i++)
	{
		array[i] = array[i+1];
	}
		
	// reduces size and returns new pos 
	size--;
	ret_pos.vsize = size;
        ret_pos.index = pos.index;

	return ret_pos;

}//remove

template<class T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2){// remove 2 params

		// checks if vector is empty or pos is out of bound 
	if(size == 0 || pos1.index >= size || pos1.index < 0)
        {
                TVectorIterator<T> itr; // returns default itr 
                return itr;
        }

	
	else if(pos1.index > pos2.index) // checks if pos1 and pos2 are invalid 
	{

          return pos1; // returns pos1

	}

	else
	{	
		// removes given range of items
 		int dif = pos2.index - pos1.index;
		for (int i = pos1.index; i < size-dif; i++)
	     		array[i]=array[i+dif];
	

		// reduces size
		size -=dif;
		pos1.ptr = (pos1.index < size) ? &array[pos1.index] : nullptr; // sets ptr based on if new index is valid or not
		pos1.vsize = size; // updates size
		return pos1; // returns pos1

	}

}// remove 2 params


template<class T>
TVectorIterator<T> TVector<T>::GetIterator() const{// GetIterator

	TVectorIterator<T> itr; // creates default iterator 

	// checks if vektor is empty
	if (size > 0)
	{
		// sets variables to vectors variables 
		itr.index = 0;
		itr.ptr = array;
		itr.vsize = size;

	}

	return itr; // returns itr

}//GetIterator

template<class T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const{
	
	TVectorIterator<T> itr;	// creates default iterator

	if(size == 0) //  checks if vektor is empty 
	{
	
	return  itr; // returns default iterator

	}


	else 
	{
        
	itr = TVectorIterator<T>(this, size);// sets iterator to last spot in array

        return itr; // returns iterator
        }


}


template<class T>
TVectorIterator<T>::TVectorIterator(){// Iterator constructor 

  // sets iterator values to default 
  index = 0;
  vsize = 0;
  ptr = nullptr;

}// Iterator constructor 




template<class T>
bool TVectorIterator<T>::HasNext() const{// HasNext
  bool status = true; // sets bool to default true

   // sets bool to false if the vector is at capacity
  if(index+1 == vsize) 
	status = false;


return status; // returns bool
}//HasNext



template<class T>
bool TVectorIterator<T>::HasPrevious() const{//HasPrevious


return index > 0; // returns whether vector is empty or not
}//HasPrevious

template <class T>
TVectorIterator<T> TVectorIterator<T>::Next(){//Next
	
         
	if (ptr != nullptr){//checks if ptr is null 

		if (HasNext()) // checks if vektor has next value
		{
			
			index++; // increments index
			ptr++;  // increments ptr

		}

	}
return *this; // returns current iterator
}//Next


template <class T>
TVectorIterator<T> TVectorIterator<T>::Previous(){ //Previous

	if(ptr != nullptr) // checks if ptr is null
	{

		if(HasPrevious()){ //checks if has previous 

                        index--; // decrements index
                        ptr--;

 		}

	}


return *this; // returns current iterator
} // previous 

template <class T>
T& TVectorIterator<T>::GetData() const{//GetData

          // checks if ptr is null
	if (ptr == nullptr) 
	{
       
         return  TVector<T>::dummy; //returns dummy if empty

	}

	return *ptr; // returns data
}//GetData


