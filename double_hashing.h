// Ali Faiyaz
// Part 2: Assignment 3 for Double Hashing
// In this file, we will implement double hashing and test using create_and_test file
// The difference from quadratic and linear is I need to implement the double hashing formula and then add to the findpos function

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace {

// Internal method to test if a positive number is prime.
bool DoubleIsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}

// Internal method to return a prime number at least as large as n.
int DoubleNextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!DoubleIsPrime(n)) n += 2;  
  return n;
}

}  // namespace

// This class is used to create a hash table using double hashing 
// in this double hashing, I implemented a new function that using the double hashing formula and create a new variable R setting it to 89
// then in the function FindPos, I used the double hashing function by adding the current position

// Double probing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(DoubleNextPrime(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x)); // this for found or not found , if true its found , not true not found
  }
 
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
  // a getter that return the size of the array current_size_;
  int get_size(){
      return current_size_;
  }
  // a getter that return the size of the table of array_ ;
  int get_table_size(){
      return array_.size();
  }
  // a getter that divide the current_size_ by the array_.size();
  float get_load_factor(){
      return (float)current_size_ / (float)array_.size();
  }
  // a getter that return the number of collisions
  int get_collisions(){
      return num_collisions_;
  }
  // a getter that return the average number of collisions by dividing the number of collisions by the size of the array_ 
  float get_average_collisions(){
      return (float)num_collisions_ / (float)current_size_;
  }
  // a getter than resets the number of collisions to 0;
  void reset_collisions(){
      num_collisions_ = 0;
  }
  
 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    
    
  std::vector<HashEntry> array_; // used the size of the array_ for the table (make a getter)
  size_t current_size_; // used for size and number of elements 
  mutable size_t num_collisions_ = 0; // this variable should be incremented every time a collision occurs and checks for it

  
  unsigned int R = 89; // setting the value of R to 89 for the double hashing function. the value R is a prime number and was printed out when running the double hashing file.

  // this double hash function is using the formula from the textbook hash2 (x) = R – (x mod R)
  size_t double_hash(const HashedObj & x) const {
    static std::hash<HashedObj> hf; 
    return R- (hf(x) % R);
 }


  bool IsActive(size_t current_pos) const
  { 
    return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
   
    size_t current_pos = InternalHash(x);  
    while (array_[current_pos].info_ != EMPTY &&
	  array_[current_pos].element_ != x) {
      num_collisions_++; // increment the number of collisions
      current_pos += double_hash(x); // current_pos = current_pos + double_hash(x). this is calling the double hash function and adding it to the current position following the formula

    if (current_pos >= array_.size())
	  current_pos -= array_.size();
    }
    return current_pos;

  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(DoubleNextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // DOUBLE_HASING_H
