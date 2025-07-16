# TVector: Custom Vector Class in C++

This project implements a custom generic vector container, `TVector<T>`, along with a bidirectional iterator 
`TVectorIterator<T>`. It replicates many behaviors of the C++ STL `vector`, including:

- Dynamic resizing
- Iterator-based access
- Insertion and removal at any position
- Overloaded `+` operator for concatenation
- Range-based deletion with iterators

## Files

- `tvector.h`: TVector class declaration and friend iterator class
- `tvector.hpp`: TVector method definitions (templated inline implementations)
- `driver.cpp`: Test program that demonstrates and verifies TVector functionality
- `Makefile`: Compiles `driver.cpp` and `tvector.hpp` into the executable `proj1.x`
- `driver_output.txt`: Sample output of the driver program for reference

## Key Features

- Constructor overloads: default, fill, copy, and move
- `Insert`, `Remove`, and `Clear` functionality
- `+` operator overload for vector concatenation
- Iterator class supporting bidirectional traversal
- Custom output formatting via `Print`

## Build Instructions

To compile:

```bash
make
