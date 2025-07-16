#include "passserver.h"

// Xian: in a shell, type "man crypt", and the MD5 can be found (which uses 22 characters of the password), and the usage will be shown as well.
// Note that it takes c_str, char [], not string directly as the input arguments. 
string PassServer::encrypt(const string & str) {
        char salt[] = "$1$########";
        char * password = new char [35];
        strcpy(password, crypt(str.c_str(), salt));

        string pword(password);
        string delim = "$";
        int pos = pword.find(delim, 0);
        pos = pword.find(delim, pos+1);
        pos = pword.find(delim, pos+1);
        pword.erase(0, pos+1);
        return pword;
}	/*char salt[] = "$1$########";
	string ret = crypt(str.c_str(), salt);
	return ret.substr(1, 22);*/




PassServer::PassServer(size_t size):h(size){// constructor which call hashtable constructor 


}


PassServer::~PassServer(){


h.clear();// calls clear on h


}


bool PassServer::load(const char *filename){


return h.load(filename); // call load on h 


}

bool PassServer::addUser(std::pair<string, string> &kv){

	if(!h.contains(kv.first)){// if username absent return false

		string  encryptPass = encrypt(kv.second); // encrypts password
		bool inserted = h.insert({kv.first, encryptPass});// inserts user
                std::cout << "user " << kv.first << " was entered" << std::endl;      
		return inserted;
	}	

	return false;
}


bool PassServer::addUser(std::pair<string, string> &&kv){


 	if(!h.contains(kv.first)){ // if username absent returns false

                string encryptPass = encrypt(kv.second); // encrypts password
                bool inserted = h.insert({kv.first, encryptPass});// inserts user
		std::cout << "user " << kv.first << " was entered"<< std::endl;
		
                return inserted;
        }       

        

	return false;
}


bool PassServer::removeUser(const string& k){


return h.remove(k); // call remove on h 

}



bool PassServer::changePassword(const std::pair<string, string> &p, const string & newpassword){

	// encrypts both passwords
        string encryptPass= encrypt(p.second);
        string newEncryptPass = encrypt(newpassword);

        if(h.match({p.first, encryptPass})){// will be true if user is in the table

                if(h.match({p.first, newEncryptPass})){ // is true if new password matches old
                return false;

                }

        bool result = h.insert({p.first, newEncryptPass});// if insert returns true 
        return result;  
        

        }
        else
        {
        return false;
        }

}

bool PassServer::find(const string& user)const{



return h.contains(user); // calls contains on h
}


void PassServer::dump()const{



h.dump(); // call dump on h 

}

size_t PassServer::size() const{


return h.size(); // return size of hash table
}


bool PassServer::write_to_file(const char* filename) const{



 return h.write_to_file(filename);// call write file on h 

}
