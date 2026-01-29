# Unit 3 Progress Check - Merge Sort

Implement merge sort.

- Your sorting algorithm should work for any data type `T` where the comparison operators (`&lt;`, `>`, etc.) are defined (e.g. string, int, double, etc.).

## Merge Sort Pseudocode

```text
def sort(data):
    left, right = split(data)
    sort(left)
    sort(right)
    return merge(left, right)

def split(data):
    evenly divide the data into two halves: left, and right
    e.g. push half the items in data into left, and the other half into right
    return left and right

def merge(left, right):
    i = 0
    j = 0
    data = []
    while i &lt; left.size and j &lt; right.size:
        if left[i] &lt; right[j]:
            data.append(left[i++])
        else:
            data.append(right[j++])
    
    One of the two (i or j) reached the end.
    Copy the remaining items from the other list into data.
    return data
    
```

