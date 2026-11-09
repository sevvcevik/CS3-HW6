# CS3 Assignment 6 – Red Black Tree (Part 1)

## What is a Binary Search Tree?

A binary search tree (BST) is a tree where:

1. Every node has **at most two children** (a left child and a right child).
2. Every value in a node's **left subtree is smaller** than the node, and every value in its **right subtree is larger**.

Because of rule 2, searching only follows **one path** from the root down: at each node you go left if the value is smaller and right if it is bigger. So searching, inserting, and removing take time proportional to the **height** of the tree.

The problem: a plain BST has no balance rules. If values are inserted in sorted order, the tree turns into a chain, its height becomes n, and every operation becomes **O(n)**.

## What is a Red Black Tree?

A red black tree is a BST that **keeps itself balanced**. Every node gets a color, red or black, and the tree must always follow these properties:

1. It is a binary tree (every node has at most two children).
2. Smaller values go left, bigger values go right (the BST property).
3. Every node is either **red** or **black**.
4. The **root is always black**.
5. **No two red nodes in a row**: a red node cannot have a red child.
6. Every path from a node down to a null leaf has the **same number of black nodes** (the *black-height*). Null leaves (`nullptr`) count as black.

These properties guarantee **O(log n)** insert and search, even for sorted input.

### How Insert keeps the tree balanced

A new node is inserted like a normal BST node and colored **red** (adding red never changes the black-height). The only rule that can break is "no two reds in a row." When the new node's parent is red, the fix depends on the **uncle** (the parent's sibling):

- **Uncle is red → recolor:** the parent and uncle become black, and the grandparent becomes red. Then check again from the grandparent. If the root became red, make it black.
- **Uncle is black or null → rotate, then recolor:**
  - **LL / RR** (straight line): one rotation at the grandparent.
  - **LR / RL** (zig-zag): rotate at the parent first to straighten it, then rotate at the grandparent.
  - The node that moved to the top becomes black, and the old grandparent becomes red.


## What's Implemented

- Constructors: default, with one value, and a deep-copy copy constructor
- Destructor and assignment operator (each tree owns its own nodes, so there are no leaks or double frees)
- `Insert(int)` with recoloring and rotations; throws `invalid_argument` on a duplicate value
- `Contains(int)`, `GetMin()`, `GetMax()` (the last two throw `invalid_argument` on an empty tree), and `Size()`
- `ToInfixString()`, `ToPrefixString()`, `ToPostfixString()`, written recursively. Nodes print as `R`/`B` plus the value, for example ` B15  R10  R30 `
- `PrivateTests()` tests the rotations, the insert fix-up, and checks every red black property on large trees

Colors are stored as integers using `#define COLOR_RED 0` and `#define COLOR_BLACK 1` in `RedBlackTree.h`.

## Files

| File | Contents |
|---|---|
| `RedBlackTree.h` | `RBTNode` struct, color definitions, class declaration |
| `RedBlackTree.cpp` | implementation of all methods and `PrivateTests()` |
| `RedBlackTreeTests.cpp` | provided tests plus my own tests |
| `RedBlackTreeTestsFirstStep.cpp` | starter tests |
| `Makefile` | builds both test programs |

## Build and Run

```bash
make                  # builds rbt-tests-first and rbt-tests
./rbt-tests-first     # starter tests
./rbt-tests           # full tests
make clean            # deletes the compiled programs
```

## Checking Memory

The Makefile compiles with `-g` (so memory tools can show line numbers) and `-Wall` (all warnings).

### Linux: valgrind

```bash
make
valgrind --leak-check=full ./rbt-tests
```

Look for:
- `ERROR SUMMARY: 0 errors` → no invalid reads/writes
- `All heap blocks were freed -- no leaks are possible` → no memory leaks

### Mac: `leaks` and AddressSanitizer

Valgrind does not run on Apple Silicon Macs, so on a Mac I used these two tools while writing my code.

**Memory leaks** with the built-in `leaks` tool:

```bash
make
leaks --atExit -- ./rbt-tests
```

Look for `0 leaks for 0 total leaked bytes` near the end.

**Memory errors** (invalid reads/writes, use after free) with AddressSanitizer, which is built into the compiler:

```bash
g++ -Wall -g -fsanitize=address RedBlackTreeTests.cpp RedBlackTree.cpp -o rbt-asan
./rbt-asan
```

If the output ends with `ALL TESTS PASSED!!` and shows no `ERROR: AddressSanitizer` report, there are no memory errors.


Note: ChatGPT is used for the README file. 