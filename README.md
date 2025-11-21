# AVL Tree Implementation (C++)
A clean, generic, and memory-safe implementation of an AVL self-balancing binary search tree in modern C++.
This project focuses on correctness, performance, and minimal dependencies, using only core C++ features.

This project includes:
* A templated `ArbreAVL<T>` class
* Recursive insertion with automatic rotations
* Efficient set-style operations (`+`, `+=`, `-`, `-=`)
* Deep copy semantics
* An in-order iterator using an internal stack (`Pile<T>`)
* A full custom test suite validating correctness *and* performance

## Features

### Balanced Insertions
All insertions maintain AVL invariants using single and double rotations.
Insertion is `O(log n)`.

### Set-Style Operators
The tree behaves like a mathematical set, supporting:

| Operator | Meaning                                         |
| -------- | ----------------------------------------------- |
| `a == b` | element-wise equality (in-order)                |
| `a += b` | union into `a`                                  |
| `a + b`  | new union tree                                  |
| `a -= b` | remove all elements from `a` that appear in `b` |
| `a - b`  | new difference tree                             |

### Deep Copies
Copy constructor and assignment operator perform a full clone of the structure.

### O(1) Size Tracking
The tree tracks its size incrementally.

### Efficient In-Order Iterator
Implements `operator*`, `operator++`, comparisons, and boolean conversion.

## Build & Run
Compile and run the test suite:

```bash
g++ -std=c++11 testtp3.cpp -O2 -o test
./test
```

## Implementation Highlights

### Rotations
Both rotation types update balance factors correctly:

* `rotationGauche(Noeud*& root)`
* `rotationDroite(Noeud*& root)`

These operations ensure the tree remains height-balanced after insertions.

### Iterator
Implements an explicit stack traversal using the custom `Pile<T>` class.

### Set Operations
Implemented without relying on STL containers — everything is done using the tree’s own iterators and structure.

### Performance
The test suite includes large-scale benchmarks (up to 2M operations) to ensure your implementation meets time constraints.

## Example Usage

```cpp
#include "arbreavl.h"
#include <iostream>

int main() {
    ArbreAVL<int> a;
    a.inserer(10);
    a.inserer(5);
    a.inserer(20);

    if(a.contient(5))
        std::cout << "5 is in the tree\n";

    for(auto it = a.debut(); it; ++it)
        std::cout << *it << " ";   // prints elements in sorted order
}
```

---

## Testing Overview

`testtp3.cpp` covers:

* basic operations
* correctness of operators
* deep copy validation
* set semantics
* iterator behaviour
* performance constraints (e.g., `taille()` must be `O(1)`)
* large-scale insertion and deletion benchmarks
* edge cases (empty trees, single-node trees, etc.)