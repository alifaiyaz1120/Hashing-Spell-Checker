// Ali Faiyaz
// Part 1: Assignment 3 
// The purpose of this file is using the linear, quadratic, and double hashing files print out total number of elements in the table (N), 
// the size of the table (T), the load factor (N/T), the total number of collisions (C), and the average number of collisions (C/N).
// Also, check whether each word is in query_words.txt is in the hash table or not and number of probes to find each words.


#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"
using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    hash_table.MakeEmpty();

    // read words from the file and insert them into the hash table
    ifstream words_file(words_filename);
    string word;
    while (words_file >> word) { 
        hash_table.Insert(word); 
        
    }
    // print out the number of elements in the table(N)
    // uses current_size_ to get the number of elements in the table 
    // made a getter function called getsize 
    cout << "number_of_elements: " << hash_table.get_size() << endl;

    // print out the size_of_table by getting the size of the array_ 
    // made a getter function get_table_size
    cout << "size_of_table: " << hash_table.get_table_size() << endl;

    // print out the load factor by dividing the number of elements by the size of the table
    // made a getter function called get_load_factor that divides current_size_ by array_.size()
    cout << "load_factor: " << hash_table.get_load_factor() << endl;

    // print out the number of collisions
    // made a variable called nums_collisions and set it to 0 and increment the variable everytime there is a collision in findpos
    // made a getter function called get_num_collisions that returns nums_collisions
    cout << "collisions: " << hash_table.get_collisions() << endl;

    // get average number of collisions
    // made a getter function called get_average_collisions that divides the number of collisions by the size of the array
    cout << "avg_collisions: " << hash_table.get_average_collisions() << endl;

    // print out words in the query file and check if its Found or Not_Found and print out the number of probes
    cout<< endl;
    ifstream query_file(query_filename);
    while (query_file >> word) {
        hash_table.reset_collisions(); // made a getter that resets the number of collisions to 0
        // used contains to check if the word is in the table
        if (hash_table.Contains(word)) { 
            cout << word << " Found " << hash_table.get_collisions()+1 << endl; // added 1 
        }
        else {
            cout << word << " Not_Found " << hash_table.get_collisions()+1 << endl;
        }
    }
     
}
// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
    LinearHashTable<string> linear_probing_table; // change to LinearHashTable
      TestFunctionForHashTable(linear_probing_table, words_filename,
      			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
	HashTableDouble<string> double_probing_table; // change to HashTableDouble
	TestFunctionForHashTable(double_probing_table, words_filename,
	 			 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
