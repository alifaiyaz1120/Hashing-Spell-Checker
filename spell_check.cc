// Ali Faiyaz
// Part 3 for Assignment 3 - Spell Checker
// In this spell_check.cc file, I checked for spelling of words based on the words.txt and words.En.txt files which is a dictionary.
// I checked for spelling of words using the document text files given to us.
// If a word is found, print out the word is correct. If not found, print out the word is incorrect.
// If its incorrect, I printed out cases that closest to the misspelled word from the dictionary.


#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you haven't implemented double hashing.
#include "double_hashing.h"
//#include "quadratic_probing.h"
using namespace std;

// this function check for punctuation at the end of the word
bool isPunct(string word) {
    if (word[word.size() - 1] == '.' || word[word.size() - 1] == ',' || word[word.size() - 1] == '!' || 
        word[word.size() - 1] == '?' || word[word.size() - 1] == ';' || word[word.size() - 1] == ':' || 
        word[word.size() - 1] == ']' || word[word.size() - 1] == '(' || word[word.size() - 1] == ')' ||
        word[word.size() - 1] == '\'' || word[word.size() - 1] == '"') {
        return true;
    }
    else {
        return false;
    }
}

// this function check for punctuation at the beginning of the word
bool isPunctFront(string word) {
    if (word[0] == '.' || word[0] == ',' || word[0] == '!' || 
        word[0] == '?' || word[0] == ';' || word[0] == ':' || 
        word[0] == '[' || word[0] == '(' || word[0] == ')'
        || word[0] == '"' || word[0] == '\'') {
        
        return true;
    }
    else {
        return false;
    }
}
// this function check for punctuation in the beginning and end of the word by calling the isPunct and isPunctFront functions
bool isPunctBoth(string word) {
    if (isPunctFront(word) && isPunct(word)) {
        return true;
    }
    else {
        return false;
    }
}
// this function check for two punctuation at the end of the word
bool isPunctTwo(string word) {
    if ((word[word.size() - 1] == '"' && word[word.size() - 2] == '.')) {
        return true;
    }
    else {
        return false;
    }
}

// Creates and fills double hashing hash table with all words from dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {

  HashTableDouble<string> dictionary_hash; 
  // read the words in the dictionary file which are word.txt and wordEn.txt
  ifstream words_file(dictionary_file);
  string word; // variable to store the words
  while (words_file >> word) {
    dictionary_hash.Insert(word); // insert the words from the dictionary file into the hash table
    //cout << word << endl;
  }
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {
   // For each word in the document_file, it checks the 3 cases for a word being misspelled and prints out possible corrections
   
    ifstream query_file(document_file); // read the words in the document file
    string word; // variable to store the words
 
    while (query_file >> word) {
    string lowercase_word = word; // a new variable that will store all the words in lowercase
    for (int i = 0; i < word.size(); i++) {
        lowercase_word[i] = tolower(word[i]); // this will convert all the words to lowercase
    }
    if (dictionary.Contains(lowercase_word)) {
          cout << lowercase_word << " is CORRECT" << endl; // if the word is in the dictionary then it is correct
    }
    else if (isPunct(lowercase_word) && !isPunctFront(lowercase_word) && !isPunctTwo(lowercase_word)) {
        // this check is there a punctuation at the end of the word
        // if there is delete the punctuation and check if the word is in the dictionary
        string word_punct = lowercase_word;
        word_punct.pop_back(); // this will delete the punctuation at the end of the word
        if (dictionary.Contains(word_punct)) {
            cout << word_punct << " is CORRECT" << endl;
        }
        else {
            cout << word_punct << " is INCORRECT" << endl; // if there no punctuation at the end of the word then it is incorrect

            // This is for Case A
            // Add a letter to the word which is close to the word in the dictionary
             for (int i = 0; i < 26; i++) {
                for (int j = 0; j < word_punct.size() + 1; j++) {
                    string word_add = word_punct; // a new variable that will store the word with the added letter
                    word_add.insert(j, 1, 'a' + i); // this will add a letter to the word
                    if (dictionary.Contains(word_add)) {
                        cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                    }
                }
            }
            // also part of Case A
            for (int i = 0; i < 26; i++) {
                string word_add = word_punct;
                word_add.insert(word_punct.size(), 1, 'a' + i); // this will add a letter within the word
                if (dictionary.Contains(word_add)) {
                    cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                }
            }

            // This is for Case B
            // Removing one character from the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size(); i++) {
                string word_remove = word_punct; // a new variable that will store the word with the removed letter
                word_remove.erase(i, 1); // erase the letter from the word close to the word in the dictionary
                if (dictionary.Contains(word_remove)) {
                    cout << "** " << word_punct << " -> " << word_remove << " ** case B" << endl; // print with new found word when the letter is removed if found in the dictionary
                }
            }

            // This is for Case C
            // Swapping two adjacent characters in the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size() - 1; i++) {
                string word_swap = word_punct; // a new variable that will store the word with the swapped letter
                swap(word_swap[i], word_swap[i + 1]); // swap the letter with the letter next to it
                if (dictionary.Contains(word_swap)) {
                    cout << "** " << word_punct << " -> " << word_swap << " ** case C" << endl; // print with new found word when the letter is swapped if found in the dictionary
                }
        }
        }
    }
    // this check is there a punctuation at the beginning of the word
    // if there is delete the punctuation and check if the word is in the dictionary
    else if (isPunctFront(lowercase_word) && !isPunct(lowercase_word)) {
 
        string word_punct = lowercase_word;
        word_punct.erase(0, 1); // this will delete the punctuation at the beginning of the word
        if (dictionary.Contains(word_punct)) {
            cout << word_punct << " is CORRECT" << endl;
        }
        else {
            cout << word_punct << " is INCORRECT" << endl; // if there no punctuation at the end of the word then it is incorrect

            // This is for Case A
            // Add a letter to the word which is close to the word in the dictionary
             for (int i = 0; i < 26; i++) {
                for (int j = 0; j < word_punct.size() + 1; j++) {
                    string word_add = word_punct; // a new variable that will store the word with the added letter
                    word_add.insert(j, 1, 'a' + i); // this will add a letter to the word
                    if (dictionary.Contains(word_add)) {
                        cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                    }
                }
            }
            // also part of Case A
            for (int i = 0; i < 26; i++) {
                string word_add = word_punct;
                word_add.insert(word_punct.size(), 1, 'a' + i); // this will add a letter within the word
                if (dictionary.Contains(word_add)) {
                    cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                }
            }

            // This is for Case B
            // Removing one character from the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size(); i++) {
                string word_remove = word_punct; // a new variable that will store the word with the removed letter
                word_remove.erase(i, 1); // erase the letter from the word close to the word in the dictionary
                if (dictionary.Contains(word_remove)) {
                    cout << "** " << word_punct << " -> " << word_remove << " ** case B" << endl; // print with new found word when the letter is removed if found in the dictionary
                }
            }

            // This is for Case C
            // Swapping two adjacent characters in the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size() - 1; i++) {
                string word_swap = word_punct; // a new variable that will store the word with the swapped letter
                swap(word_swap[i], word_swap[i + 1]); // swap the letter with the letter next to it
                if (dictionary.Contains(word_swap)) {
                    cout << "** " << word_punct << " -> " << word_swap << " ** case C" << endl; // print with new found word when the letter is swapped if found in the dictionary
                }
        }
        }
    }
    // this checks if there are punctuation at the beginning and end of the word
    // if so, delete both punctuation and check if the word is in the dictionary
    else if (isPunctBoth(lowercase_word)) {
        string word_punct = lowercase_word;
        word_punct.erase(0, 1); // this will delete the punctuation at the beginning of the word
        word_punct.pop_back(); // this will delete the punctuation at the end of the word
        if (dictionary.Contains(word_punct)) {
            cout << word_punct << " is CORRECT" << endl;
        }
        else {
            cout << word_punct << " is INCORRECT" << endl; // if not in the dictionary its incorrect

            // This is for Case A
            // Add a letter to the word which is close to the word in the dictionary
             for (int i = 0; i < 26; i++) {
                for (int j = 0; j < word_punct.size() + 1; j++) {
                    string word_add = word_punct; // a new variable that will store the word with the added letter
                    word_add.insert(j, 1, 'a' + i); // this will add a letter to the word
                    if (dictionary.Contains(word_add)) {
                        cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                    }
                }
            }
            // also part of Case A
            for (int i = 0; i < 26; i++) {
                string word_add = word_punct;
                word_add.insert(word_punct.size(), 1, 'a' + i); // this will add a letter within the word
                if (dictionary.Contains(word_add)) {
                    cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                }
            }

            // This is for Case B
            // Removing one character from the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size(); i++) {
                string word_remove = word_punct; // a new variable that will store the word with the removed letter
                word_remove.erase(i, 1); // erase the letter from the word close to the word in the dictionary
                if (dictionary.Contains(word_remove)) {
                    cout << "** " << word_punct << " -> " << word_remove << " ** case B" << endl; // print with new found word when the letter is removed if found in the dictionary
                }
            }

            // This is for Case C
            // Swapping two adjacent characters in the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size() - 1; i++) {
                string word_swap = word_punct; // a new variable that will store the word with the swapped letter
                swap(word_swap[i], word_swap[i + 1]); // swap the letter with the letter next to it
                if (dictionary.Contains(word_swap)) {
                    cout << "** " << word_punct << " -> " << word_swap << " ** case C" << endl; // print with new found word when the letter is swapped if found in the dictionary
                }
        }
        }
    }
    // if there two punctuation at the end of the word, delete the last two punctuation
    // then, check if its in the dictionary or not 
    else if (isPunctTwo(lowercase_word))
    {
        string word_punct = lowercase_word;
        word_punct.pop_back(); // this will delete the punctuation at the end of the word
        word_punct.pop_back(); // this will delete the 2nd punctuation at the end of the word
        if (dictionary.Contains(word_punct)) {
            cout << word_punct << " is CORRECT" << endl;
        }
        else {
            cout << word_punct << " is INCORRECT" << endl; // if not in the dictionary its incorrect

            // This is for Case A
            // Add a letter to the word which is close to the word in the dictionary
             for (int i = 0; i < 26; i++) {
                for (int j = 0; j < word_punct.size() + 1; j++) {
                    string word_add = word_punct; // a new variable that will store the word with the added letter
                    word_add.insert(j, 1, 'a' + i); // this will add a letter to the word
                    if (dictionary.Contains(word_add)) {
                        cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                    }
                }
            }
            // also part of Case A
            for (int i = 0; i < 26; i++) {
                string word_add = word_punct;
                word_add.insert(word_punct.size(), 1, 'a' + i); // this will add a letter within the word
                if (dictionary.Contains(word_add)) {
                    cout << "** " << word_punct << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                }
            }

            // This is for Case B
            // Removing one character from the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size(); i++) {
                string word_remove = word_punct; // a new variable that will store the word with the removed letter
                word_remove.erase(i, 1); // erase the letter from the word close to the word in the dictionary
                if (dictionary.Contains(word_remove)) {
                    cout << "** " << word_punct << " -> " << word_remove << " ** case B" << endl; // print with new found word when the letter is removed if found in the dictionary
                }
            }

            // This is for Case C
            // Swapping two adjacent characters in the word and look at the dictionary for the new word
            for (int i = 0; i < word_punct.size() - 1; i++) {
                string word_swap = word_punct; // a new variable that will store the word with the swapped letter
                swap(word_swap[i], word_swap[i + 1]); // swap the letter with the letter next to it
                if (dictionary.Contains(word_swap)) {
                    cout << "** " << word_punct << " -> " << word_swap << " ** case C" << endl; // print with new found word when the letter is swapped if found in the dictionary
                }
        }
        }
    }
    else
    {
        cout << lowercase_word << " is INCORRECT" << endl; // if not in the dictionary its incorrect
     
        // This is for Case A
        // Add a letter to the word which is close to the word in the dictionary
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < lowercase_word.size() + 1; j++) {
                string word_add = lowercase_word; // a new variable that will store the word with the added letter
                word_add.insert(j, 1, 'a' + i); // this will add a letter to the word
                if (dictionary.Contains(word_add)) {
                    cout << "** " << lowercase_word << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
                }
                word_add = lowercase_word;
            }
        }
        
        // also part of Case A
        for (int i = 0; i < 26; i++) {
            string word_add = lowercase_word;
            word_add.insert(lowercase_word.size(), 1, 'a' + i); // this will add a letter within the word
            if (dictionary.Contains(word_add)) {
                cout << "** " << lowercase_word << " -> " << word_add << " ** case A" << endl; // print with the word with the added letter if found in the dictionary
            }
            word_add = lowercase_word;
        }

         // This is for Case B
         // Removing one character from the word and look at the dictionary for the new word
        for (int i = 0; i < lowercase_word.size(); i++) {
            string word_remove = lowercase_word; // a new variable that will store the word with the removed letter
            word_remove.erase(i, 1);  // erase the letter from the word close to the word in the dictionary
            if (dictionary.Contains(word_remove)) {
                cout << "** " << lowercase_word << " -> " << word_remove << " ** case B" << endl; // print with new found word when the letter is removed if found in the dictionary
            }
        }
        
        // This is for Case C
        // Swapping two adjacent characters in the word and look at the dictionary for the new word
        for (int i = 0; i < lowercase_word.size() - 1; i++) {
            string word_swap = lowercase_word; // a new variable that will store the word with the swapped letter
            swap(word_swap[i], word_swap[i + 1]); // swap the letter with the letter next to it
            if (dictionary.Contains(word_swap)) {
               cout << "** " << lowercase_word << " -> " << word_swap << " ** case C" << endl;  // print with new found word when the letter is swapped if found in the dictionary
            }
        }
                
        }
        
    }
    
    }
    
// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}

