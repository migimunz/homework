# Homework Two

Implement a simple simulation of [semi-space garbage collection][1] in C++. From
the linked Wikipedia article:

>  The most straightforward approach is the _semi-space_ collector,  which dates
to 1969.  In this moving collector,  memory is partitioned into an equally sized
"from space"  and  "to space".  Initially,  objects are  allocated in "to space"
until it becomes full  and a collection cycle is triggered.  At the start of the
cycle, the  "to space"  becomes the  "from space",  and vice versa.  The objects
reachable from the root set are copied from  the "from space" to the "to space".
These objects are scanned in turn, and all objects that they point to are copied
into  "to space",  until all reachable objects have been copied into "to space".
Once the program continues  execution,  new objects are once again  allocated in
the "to space" until it is once again full and the process is repeated.

Your program  should read a single integer  as a command line argument - this is
the size of the stack  (which you will divide into two equal regions) - and then
read a series of commands from standard input.  These commands can be any of:

 - **Allocate:** `a[ID]:[SIZE]`  
   If your program sees `a1:20` it should allocate a region with ID 1 and a size
   of 20 bytes.  Only `SIZE` bytes should go onto the simulated heap. You should
   keep track of any heap  metadata separately.  If there is not enough room for
   the new object, run garbage collection. If there is no room on the heap after
   garbage collection, print `Not enough space.` to `stdout`.
 - **Reference:** `r[ID]`  
   If your program sees `r4`, it should note that there is one more reference to
   object `4`. Objects cannot be cleaned up until their reference counts drop to
   zero.
 - **Dereference:** `d[ID]`  
   If your program sees `d7`, it should note that there is one less reference to
   object `7`.  If that object's reference count drops to zero, it is _eligible_
   for garbage collection.
 - **List:** `l`  
   If your program sees `l`,  it should print the state of the current simulated
   heap. Each object should be printed in order as `[ID]:[SIZE]@[OFFSET]#[REFS]`
   (`OFFSET`  being the object's offset  within the active memory region),  with
   each object on its own line.
 - **Exit:** `x`  
   If your program sees `x`, it should exit.

Commands will be separated with whitespace (spaces, tabs, or newlines). IDs will
be positive integers.  We will never send your program invalid commands.

An example run (note that garbage collection runs twice,  once before failing to
allocate `a3` and once before successfully allocating `a4`):

```
[bashorwhatever]$ ./a.out 20
a1:4
a2:5
a3:6
Not enough space.
l
1:4@0#1
2:5@4#1
r2
d1
a4:3
a5:2
d4
l
2:5@0#2
4:3@5#0
5:2@8#1
x
```

Implementation details (so we can auto-grade):
 - Garbage collection should only run when an allocation is requested, but won't
   fit in the current memory block.
 - Always allocate objects at the smallest available offset (starting at 0).
 - When running garbage collection, preserve the order of all objects.

[1]: https://en.wikipedia.org/wiki/Tracing_garbage_collection#Copying_vs._mark-and-sweep_vs._mark-and-don.27t-sweep
