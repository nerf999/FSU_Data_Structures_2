This repository contains a collection of C++ projects completed as part of my coursework at Florida State University (BS in Computer Science). 
Each project progressively builds foundational and advanced skills in object-oriented programming, data structure implementation, and algorithmic thinking.



Project 1 – Custom Vector Class
A full implementation of a templated dynamic array class TVector<T>, mimicking key features of the C++ STL vector. Supports:

Copy/move constructors and assignment

Dynamic resizing and capacity control

Iterator support and insert/remove operations

Print and utility methods



Project 2 – Doubly Linked List
A templated doubly linked list class with:

Custom iterators

Insert/erase methods at arbitrary positions

Deep copy and assignment support

Range-based operations and initializer list support




Project 3 – Binary Expression Tree
A BET class that parses postfix expressions and builds binary trees to:

Convert postfix to infix (with correct parentheses)

Support copy, assignment, size, and leaf counting

Traverse and print in postfix and infix notation

Prevent memory leaks via proper recursive cleanup




Project 4 – Password Server with Hash Table Backend
A secure password manager built on a custom templated HashTable<K, V> implementation:

Uses crypt() for password encryption

Supports adding, removing, and updating users

Saves/loads data from files

Demonstrates dynamic hashing with separate chaining


 Tools & Technologies
C++11 Standard

Custom Makefiles

Unix/Linux Development Environment (Tested on linprog)

STL Containers (vector, list, pair)



