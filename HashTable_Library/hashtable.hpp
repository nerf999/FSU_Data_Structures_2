template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long> & vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
 HashTable<K, V>::HashTable(size_t size){


 size_t Test = prime_below(size);// gets prime number 

	if (Test  == 0)// if zero sets size to default 
 	{
		currentSize = 0;
		theLists.resize (101);

	}
	else // if non zero hashtable is set as size
	{
		currentSize = 0;
		theLists.resize(Test);
	
	}


std::cout << "In total there are " << theLists.size() << " rows in the vector." << std::endl;// tells user size of vector
}

template <typename K, typename V>
 HashTable<K, V>::~HashTable(){

	theLists.clear();// clears table 

	currentSize = 0;// sets size to 0 

}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const{


	size_t index = myhash(k); // index is found with hash  

         bool status = false;// sets initial status false 

        for (const auto& pair : theLists[index]) {// goes through each list in vector
                if (pair.first == k) {// check K with list pair 
                status = true;           
                }
        }
   
        return status;

}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k)const{

	static hash<K> hf;
	return hf(k) % theLists.size();

}

template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> &kv)const{

	bool status = false;

	size_t index = myhash(kv.first);// finds index with hash  
	
	for (const auto& pair : theLists[index]) {// iterates through vector lists
        	if (pair == kv) { 
            	status = true;  
        	}
    	}

	return status;
}


template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V> &kv){
 auto& whichList = theLists[myhash(kv.first)];  // Get the list where this key should be located.

	for (auto& item : whichList) {
		if (item.first == kv.first) {  // Key is found
			if (item.second != kv.second) {  // Check if the value differs
				item.second = kv.second;  // Update the value.
				return true;  // Value was updated.
			}
		return false;  // The exact key-value pair already exists, no update needed.
		}
	}

    // Key is not found, insert new key-value pair.
	whichList.push_back(kv);

	if (++currentSize > theLists.size()) {// increases size 
	rehash();  // Rehash 
	}
	return true;  
}

template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V> &&kv){
auto& whichList = theLists[myhash(kv.first)];  // Get the list where this key should be located.
size_t hashIndex = myhash(kv.first);


        for (auto& item : whichList) {
                if (item.first == kv.first) {  // Key is found
                        if (item.second != kv.second) {  // Check if the value differs
                                item.second = std::move(kv.second);  // Update the value.
                                return true;  // Value was updated.
                        }
                return false;  // The exact key-value pair already exists, no update needed.
                }
        }

    // Key is not found, insert new key-value pair.
        whichList.push_back(std::move(kv));
        if (++currentSize > theLists.size()) {// increase size
        rehash();  // Rehash 
        }
        return true; 



}


template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k){



        size_t index = myhash(k);  // find index with hash
	
	auto& bucket = theLists[index]; // iterate through vector lists to find right item to remove 
	for(auto it = bucket.begin(); it != bucket.end(); ++it){
		if(it->first == k){
			
			bucket.erase(it);// erases item
			return true;
		}
	

	}

	return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear(){

	makeEmpty();// calls makeempty

}


template<typename K, typename V>
 size_t HashTable<K, V>::size() const {

size_t filledSlots = 0;// sets fille slots to zero

        for(auto& bucket : theLists){ // iterates through vector looking for filled lists
		filledSlots = filledSlots + bucket.size();
	}

return filledSlots;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty(){

 for (auto& list: theLists){// iterates through vector clearing lists 

	currentSize=0;
        list.clear();
        }

}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename){
 ifstream fh(filename); //set up file stream

	if(!fh){// if not in file

	cout<<"file not found "<< endl;
	return false;
	}

	K k;
	V v;
	
	while(fh>> k >> v){// sends file contents to file stream

		if(contains(k)){// if items found 
		
		cout<<"key exists already"<<endl;
		continue;
		
		}
		auto kv = make_pair(k,v);
		insert(kv);// inserts item
		

	}
	


	fh.close();// closes filestream
	return true;
}


template<typename K, typename V>
void HashTable<K, V>::rehash(){

 vector<list<pair<K, V>>> oldLists = theLists;// makes temp space

 theLists.resize(prime_below(2*theLists.size()) );// resizes array 
 for(auto& thisList: theLists)
	thisList.clear();// clears lists

	currentSize = 0;
	for(auto& thisList: oldLists)// iterates through vector and adds users to new vector
		for(auto& x : thisList)
			insert(std::move(x));
	
}


 
template<typename K, typename V>
void HashTable<K, V>::dump()const{

	cout << "In dump, in total there are " << theLists.size() << " rows in the vector." << endl;
	for (size_t i = 0; i < theLists.size(); ++i) {
	cout << "v[" << i << "]: ";
	if (!theLists[i].empty()) {
		auto it = theLists[i].begin();
			cout << it->first << " " << it->second;  

	for (++it; it != theLists[i].end(); ++it) {
                cout << ":" << it->first << " " << it->second;  
		}
		cout << ".";  // Add a period at the end of entries for each row
		}
		cout <<endl;  // Ensure each row is output on a new line
    	}
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename)const{

ofstream fh (filename);


 if(!fh){

        cout<<"error"<< endl;
        return false;              
        }  


	for (const auto& list : theLists) {  // Iterate through each bucket
		
		for (const auto& entry : list) {  // Iterate through each entry in the list
			
			fh << entry.first << " " << entry.second << endl;  // Write key and value separated by a space
		}
    
	}




 fh.close();
 return true;


}








