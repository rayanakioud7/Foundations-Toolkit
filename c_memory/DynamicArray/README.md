
# C Dynamic Array (Manual Memory Management)

> A ground-up implementation of a dynamic array in C, designed to enforce mastery of manual heap allocation, pointer arithmetic, and memory safety.

## The Memory Model

A robust dynamic array requires two distinct levels of heap allocation to separate metadata from the payload:

1. **The Envelope (Struct):** Allocated on the heap, holding the metadata (`data` pointer, `size`, `capacity`).
2. **The Contents (Data Array):** A contiguous block of integers pointed to by `arr->data`.

```text
Stack:                Heap:
+-----------+        +----------------------+        +-------------------+
| arr ptr   | ---->  | DynamicArray struct  | ---->  | int data array    |
+-----------+        | - data ptr           |        | [0][0][0][0]...   |
                     | - size = 0           |        +-------------------+
                     | - capacity = cap     |
                     +----------------------+
```

## Mathematical Grounding

The core engineering challenge is the `append` (push) operation. If we call `realloc` on every insertion, the time complexity is $O(N)$ per operation, resulting in $O(N^2)$ total time for $N$ insertions.

By implementing a geometric growth strategy (doubling capacity when full), we achieve **Amortized $O(1)$** time complexity. The total time $T(N)$ for $N$ insertions is bounded by:

$$
T(N) = \sum_{i=1}^{N} O(1) + \sum_{k=1}^{\log_2 N} O(2^k) = O(N)
$$

This proves that the average cost per insertion remains constant, even though individual insertions occasionally trigger a costly $O(N)$ memory copy.

## Implementation Details

- **Growth Strategy:** Capacity doubles (`capacity * 2`) strictly when `size == capacity`. An initial capacity of 0 safely initializes to 1.
- **Memory Safety:** `realloc` is only invoked when the array is full. The return value of `realloc` is assigned to a temporary pointer and checked for `NULL` before overwriting `arr->data`. This prevents memory leaks and dangling pointers if the OS denies the allocation.
- **Bounds Checking:** `get` and `set` operations explicitly verify the target index against `size` before dereferencing memory.
- **Cleanup:** `dynarray_free` explicitly frees the inner `data` array before freeing the outer struct, preventing orphaned heap blocks.

## Memory Validation (Valgrind)

The implementation is verified to be memory-safe. Valgrind output after a full test suite (create, append, get, set, free):

```text
==8723== HEAP SUMMARY:
==8723==     in use at exit: 0 bytes in 0 blocks
==8723==   total heap usage: 5 allocs, 5 frees, 1,104 bytes allocated
==8723== 
==8723== All heap blocks were freed -- no leaks are possible
==8723== ERROR SUMMARY: 0 errors from 0 contexts
```

## Performance Benchmark

Comparative benchmark between Naive Realloc (reallocating on every push) and the Doubling Strategy (amortized push) for 10,000 elements.

| Operation | Naive Realloc | Doubling Strategy (Amortized) |
| :--- | :--- | :--- |
| **Total Time** | *[To be filled after benchmark]* | *[To be filled after benchmark]* |
| **Time Complexity** | $O(N^2)$ | $O(N)$ total / $O(1)$ amortized |

## Build & Execution

Compile with strict warnings and debug symbols to ensure Valgrind can map errors to specific source lines.

```bash
# Compile with strict flags
gcc -g -Wall -Wextra -Werror DynamicArray-MVP.c -o dynarray

# Run the test suite
./dynarray

# Profile for memory leaks and invalid accesses
valgrind --leak-check=full --show-leak-kinds=all ./dynarray
```

*Built as part of the `foundations-toolkit` Master Plan.*
