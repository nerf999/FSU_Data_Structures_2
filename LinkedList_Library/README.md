# Custom Doubly Linked List (`List<T>`)

This project implements a templated, bidirectional, doubly linked list class `List<T>`, mimicking
 and extending functionality similar to `std::list`. The list supports standard operations such as insertion, deletion, iteration, and comparison. 
It also includes support for initializer lists, custom predicates, and iterator-based range operations.

## Files

- `List.h`: Contains the implementation of the templated `List<T>` class and its nested iterator classes.
- `test_list.cpp`: A comprehensive driver program that demonstrates the functionality and correctness of `List<T>`.
- `makefile`: Compiles `test_list.cpp` into an executable.

## Features

- Doubly linked list with dummy head/tail nodes
- Templated `List<T>` and nested `iterator`/`const_iterator` classes
- Overloaded operators:
  - `==`, `!=` for comparison
  - `<<` for output
- Supports:
  - `push_front`, `push_back`, `pop_front`, `pop_back`
  - `insert`, `erase`, `clear`, `reverse`
  - Range-based erasure: `erase(start, end)`
  - `remove_if(Predicate)` with functors or lambdas
  - Move semantics
- Compatible with range-based `for` loops

## Example Operations Demonstrated in `test_list.cpp`

- Construction from initializer lists, iterators, and copy/move constructors
- Conditional removal using function objects (`isOdd`, `LongerThanFive`)
- Comparison of list contents using `==` / `!=`
- Range-based deletion using iterator boundaries
- Reversing and clearing lists
- Separate tests for `List<int>` and `List<std::string>`

## Build Instructions

To compile:

```bash
make
