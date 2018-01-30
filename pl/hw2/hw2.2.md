# Assignment Two

In this assignment, you will implement a simulation of semi-space garbage
collection.

Semi-space collectors are "mark and don't sweep" collectors.  They work by
partitioning the available memory into two equal halves, known as "to-space" and
"from-space."  New objects are allocated into from-space at the next available
byte (an incrementing "bump pointer" keeps track of this location).

When the next allocation would not fit in the remaining from-space, garbage
collection is triggered. The collector copies all objects reachable from a "root
set" of known reachable variables into to-space, updating pointers to point at
the objects' new locations.  Copies, like allocations, are always made at the
next available byte, with a bump pointer tracking the next free byte.  Once
garbage collection is complete, the designations of "from-space" and "to-space"
are swapped, the allocation is made into the new from-space (if it fits), and
the program continues.


## Your Assignment

You will be provided with framework C++ code that handles input, output and
testing.  Your job will be to fill in the missing methods on the `Heap` class
so that garbage collection works correctly:

 - `myptr Heap::allocate(Type t)`  
   This method should allocate enough space to hold a `t` object on the heap and
   return a pointer to that space.  This will actually consume `4 + sizeof(t)`
   bytes of heap space, so you can store heap metadata (in this case, a pointer
   to the `Type` of the allocated object).  The metadata must come before the
   space allocated for the object.  If there is not enough room on the heap,
   this method should call:

 - `void Heap::collect()`  
   This method should iterate over all objects reachable from the root set and
   copy them from from-space to to-space.  When traversing the object graph, use
   a depth-first search, copying objects as soon as you encounter them.  Parents
   should be copied before their children.  Members should be copied in
   alphabetical (technically asciibetical) order, by member name.

 - Whenever your `allocate()` method successfully allocates memory, it should
   print `"Allocated %d byte(s).\n"` to `std::cout` (with `%d` replaced with the
   appropriate integer).  If, even after garbage collection, there is not enough
   space on the heap, `allocate()` should print `"Not enough space.\n"` to
   `std::cout` and return `0`.


## An Example

Suppose you have an object graph like this (lower case letters are variables in
the root set; upper case letters are objects):

```
x     y   z
↓    ↙ ↘ ↙
A ← B   C
↓↘  ↓
E D G     F
```

By the rules above, running garbage collection on that graph will result in a
to-space that looks like this (assume the members of object `A` were such
that `A.d = D` and `A.e = E`, so the order was imposed by alphabetizing):

```
|[A][D][E][B][G][C]--------|
```
