# Hashing and Spell Checker 

## Overview
By: Ali Faiyaz

This programming assignment involves implementing and testing three hashing techniques (quadratic probing, linear probing, and double hashing) and utilizing the best-performing one for a spell-checker. The assignment includes three main components:

1. `create_and_test_hash.cc`: Program to test hashing implementations.
2. `spell_check.cc`: Program for spell-checking using the best-performing hashing technique.
3. Hashing Header Files:
   - `linear_probing.h`: Header file for linear probing.
   - `quadratic_probing.h`: Header file for quadratic probing.
   - `double_hashing.h`: Header file for double hashing.

## Part 1: Hashing (create_and_test_hash.cc)
**Usage:**
```bash
./create_and_test_hash <words file name> <query words file name> <flag>
```
- "words file name": Name of the file containing words for building the hash table.
- "query words file name": Name of the file containing words for testing the hash table.
- "flag": Use "quadratic" for quadratic probing, "linear" for linear probing, and "double" for double hashing.

Example: 
```bash
./create_and_test_hash words.txt query_words.txt quadratic

```

Output Format:
```bash
number_of_elements: 500 
size_of_table: 1350 
load_factor: 0.37037037 
collisions: 3 
avg_collisions: 0.006
law Found 1
factz Not_Found 3
book Found 1
...
```
## Part 2: Double Hashing (create_and_test_hash.cc)
**Usage:**
```bash
./create_and_test_hash words.txt query_words.txt double <R VALUE>
```
- "R VALUE": R-value for double hashing as discussed in class.

### Example:
```bash
./create_and_test_hash words.txt query_words.txt double 7

```

Output Format:
```bash
r_value: 7
<SAME FORMAT AS LINEAR / QUADRATIC>
law Found 1
factz Not_Found 3
book Found 1
...

```
## Part 3: Spell Checker (spell_check.cc)
**Usage:**
```bash
./spell_check <document file> <dictionary file>
```
- "document file": Name of the document file to be spell-checked.
- "dictionary file": Name of the dictionary file containing valid words.

### Example 
```bash
./spell_check document1.txt wordsEN.txt
```
Output Format:
```bash
complete is CORRECT
deciasion is INCORRECT
** deciasion -> decision ** case B
lwa is INCORRECT
** lwa -> wa ** case B
** lwa -> la ** case B
** lwa -> law ** case C
...

```
