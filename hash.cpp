/*
 * Programming Challenge 3
written by Sean McDonald
finished 3/24/16
updated 3/24/16

References
Cplusplus.com 
wikipedia for the idea of bitshift hash idea and CRC32

 */

#include "hash.h"
#include <fstream>
#include <iomanip>

//constructor that will set the number of collisions to 0
//and the average list length to 0
Hash::Hash()
 : collisions(0),runningAvgListLength(0)
{}


//@param string contents holds the string that will be removed 
//from the hash table
void Hash::remove(string contents) {
	for(std::list<string>::iterator i= hashTable[hf(contents)].begin();
	i != hashTable[hf(contents)].end(); i++) {
		//if the string is found delete it and decrement the number of 
		//items and update the average length
		if(contents==*i) {
			i=hashTable[hf(contents)].erase(i);
			num_items--;
			//after deleted check to see if the list is empty, if it is update
			//the number of elements in the array being used and the av length
			if (hashTable[hf(contents)].empty()) {
				num_array--;
			}
			updateavg();
		}
	}
}

//will print out the entire hashtable
void Hash::print(){
   //iterate through the array
    for (int z=0;z<HASH_TABLE_SIZE;z++) {
    	std::cout<<z<<":\t";
    	//iterate through the list
    	for(std::list<string>::const_iterator i=hashTable[z].begin();
    	   i!=hashTable[z].end();i++){
    			//print out the string
    			std::cout<<*i<< ", ";
    	}
    	std::cout<< "\n";
    }
}                 

//@param filename the name of the file that will have data extracted
void Hash::processFile(string filename){
   //a string that will hold the data taken from the file
	string testy;
	std::ifstream file(filename);
	//check goodbit
	if (file.good()) {
	   //while there is input to process
		while(getline(file,testy)) {
		   //if the element is not empty there is a collision, add hash 
			if (!hashTable[hf(testy)].empty()) {
				hashTable[hf(testy)].push_back(testy);
				collisions++;
				num_items++;
			}
			else {
			   //if it is empty increment the number of used arrays 
			hashTable[hf(testy)].push_back(testy);
			num_items++;
			num_array++;
			
			}
			updateavg();
			//if the element that just had the string pushed back is larger
			//than the previous longestList, it will be the new one
			if(hashTable[hf(testy)].size()>longestList) {
				longestList=hashTable[hf(testy)].size();
			}
		}
	}
}
//@param string contents
//@return bool return true if the string was found
bool Hash::search(string contents) {
    for(std::list<string>::const_iterator i= hashTable[hf(contents)].begin();
    i != hashTable[hf(contents)].end(); i++) {
		if(contents==*i) {
		return true;	
		}
	}  
return false;
}

//@param string filename will be the filename we will write to
void Hash::output(string filename){
    std::ofstream outs;
    outs.open(filename);
    //iterate through the elements of the array
    for (int z=0;z<HASH_TABLE_SIZE;z++) {
    	outs<<z<<":\t";
    	//iterate through the hashes on each element 
    	for(std::list<string>::const_iterator i= hashTable[z].begin();
    	   i != hashTable[z].end(); i++) {
    	      //write the current string to the outfile
    			outs<<*i<< ", ";
    	}
    	if(z<HASH_TABLE_SIZE-1) {
    		outs<< "\n";
    	}
    }
    outs.close();
}

void Hash::updateavg() {
   runningAvgListLength=(runningAvgListLength+
   ((double)(num_items)/((double)num_array)))/2;
}

//print out all of the misc facts about the program
void Hash::printStats() {
	std::cout << "Total Collisions = "<<collisions<<std::endl;
	std::cout <<"Longest List Ever = " << longestList<<std::endl;
	std::cout << "Average List Length Over Time = ";
    std::cout<<runningAvgListLength<<std::endl;
	std::cout <<"Load Factor = ";
	double load_factor=((double)num_items/((double)HASH_TABLE_SIZE));
	std::cout<<load_factor<<std::endl;
}
