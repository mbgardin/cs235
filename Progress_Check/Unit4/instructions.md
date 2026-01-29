# Unit 4 Progress Check - Devector

A double-ended vector (devector) is a vector-like data structure
that allows \(O(1)\) push/pop operations on **both** ends,
while preserving constant-time random access (i.e. indexing).

Your task is to implement a devector.

## Details

Devector's use the concept of a *circular buffer*.
They store an array to hold the items, just like a vector.
However, in addition to a value named `size` that indicates how many items are stored,
devectors track an additional value named `front`.

Consider the following sequence. The buffer starts empty (`f` will indicate the value of `front`):

```text
size=0
f
0   1   2   3   4   5   6
```

`push_back` `a`, `b`, `c`, `d`, `e`, `f`, `g`:

```text
size=7
f
0   1   2   3   4   5   6
a   b   c   d   e   f   g
```

Now `pop_front` twice:

```text
size=5
        f
0   1   2   3   4   5   6
a   b   c   d   e   f   g
```

Now `push_back` `x` (note: `front + size = 5 + 2 = 7`, which wraps to `0`, which is where the item goes):

```text
size=6
        f
0   1   2   3   4   5   6
x   b   c   d   e   f   g
```

Consider this different sequence of operations:

```text
size=0
f
0   1   2   3   4   5   6
```

`push_back` `a`, `b`, `c`:

```text
size=3
f
0   1   2   3   4   5   6
a   b   c
```

Now `push_front` `x`, `y`, `z`:

```text
size=6
                f
0   1   2   3   4   5   6
a   b   c       z   y   x
```

Note that `(front - 1) = (0 - 1) = -1`, which wraps to `6`, which is where the `x` goes.

### Growing

Just like with `vector`, once every slot in the buffer is full and you want to add a new item,
you need to grow the buffer.

Create a new buffer, copy the items over from the old buffer, and proceed.

Let's say we have the following state:

```text
                f         
0   1   2   3   4   5   6
q   b   x   y   t   s   r
```

We `push_back` a `z`, but before adding the `z`, we grow, then add the `z`:

```text
                f         
0   1   2   3   4   5   6
q   b   x   y   t   s   r

f
0   1   2   3   4   5   6   7   8   9  10  11  12  13
t   s   r   q   b   x   y   z

```

### Conclusion

Using a double-ended vector with a circular buffer gives us all the performance benefits of a vector,
including constant-time random access, while also providing constant time push/pop operations on **both**
ends of the sequence.

## Assignment

Implement the provided Devector class.

### Grading

| Test                                    | Points  |
|-----------------------------------------|---------|
| constructor_destructor_const_size_empty | 5       |
| push_pop_front_size                     | 5       |
| push_pop_back_size                      | 5       |
| push_back_contents                      | 5       |
| push_front_contents                     | 5       |
| push_back_grow_contents                 | 5       |
| push_front_grow_contents                | 5       |
| front_back_grow_clear_size              | 5       |
| operator_bracket_assignment             | 5       |
| at                                      | 5       |
| push_pop_contents                       | 15      |
| grow                                    | 10      |
| performance                             | 20      |
| no memory leaks                         | 5       |
| **Total**                               | **100** |
