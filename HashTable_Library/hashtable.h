#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;
 
namespace cop4530
{
    template <typename K, typename V>
    class HashTable
    {
      public:

	explicit HashTable(size_t size = 101);//done

	~HashTable(); // done

	// Xian: different from the book as we have a pair instead of one key. 
	// Use key to locate the place in the vector. But save both key and value as a pair.
	bool contains(const K & k) const; // done

	bool match(const std::pair<K, V> &kv) const;// done

	bool insert(const std::pair<K, V> & kv); //done

	// Xian: how to deal with first and second component for kv in this case?
	bool insert(std::pair<K, V> && kv);// done

	bool remove(const K & k);//done

	void clear();// done

	bool load(const char *filename);

	void dump() const;

	size_t size() const;// done 

	bool write_to_file(const char *filename) const;

      private:

	vector<list<pair<K, V>>>  theLists; // val

	int currentSize; // val

	void makeEmpty(); // DONE

	void rehash();// done

	size_t myhash(const K & k) const; // done

	unsigned long prime_below(unsigned long n); // DONE
        
	void setPrimes(vector<unsigned long> & vprimes); //DONE
        
    }; // end of HashTable

    #include "hashtable.hpp"

} // end of namespace
#endif
