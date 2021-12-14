# Segment Trees

Let us say we have an array $a$ of $n$ elements. Now we need to process queries $sum(l,r)$ where $0 \leq l \leq r$ and $update(i,x)$ i.e. $a[i] = x$. The naive method for $sum$ would be traverse over the array and add the elements, and for update we can do it in constant time. 

Hence, $O(n)$ complexity for $sum(l,r)$ and $O(1)$ complexity for $update(i,x)$. 

However, in case there are a large number of $sum$ queries, this method would be extremely inefficient. This is where **Segment Trees** come in. They provide a much more efficient way of processing the $sum(l,r)$ queries. We shall first look at the construct of the data structure and then analyse the complexities.

Foolowing is the pictorial representation of a segment tree:

![](img5.png)

## Construction
We compute and store the sum of the elements of the whole array, i.e. the sum of the segment $a[0…n−1]$. We then split the array into two halves $a[0…n/2]$ and $a[n/2+1…n−1]$ and compute the sum of each half and store them. Each of these two halves in turn also split in half, their sums are computed and stored. And this process repeats until all segments reach size 1. In other words we start with the segment $a[0…n−1]$, split the current segment in half (if it has not yet become a segment containing a single element), and then calling the same procedure for both halves. For each such segment we store the sum of the numbers on it.

We can say, that these segments form a binary tree: the root of this tree is the segment $a[0…n−1]$, and each vertex (except leaf vertices) has exactly two child vertices.

> Height of the tree: $logn$

Number of vertices required:

$2^0 + 2^1 + ..... + 2^h \leq 4n$ where $h = logn$

Before constructing the segment tree, we need to decide:

1. The value that gets stored at each node of the segment tree. For example, in a sum segment tree, a node would store the sum of the elements in its range $[l,r]$.
2. The merge operation that merges two siblings in a segment tree. For example, in a sum segment tree, the two nodes corresponding to the ranges $a[l1…r1]$ and $a[l2…r2]$ would be merged into a node corresponding to the range $a[l1…r2]$ by adding the values of the two nodes.

Now, for construction of the segment tree, we start at the bottom level (the leaf vertices) and assign them their respective values. On the basis of these values, we can compute the values of the previous level, using the *merge* function. And on the basis of those, we can compute the values of the previous, and repeat the procedure until we reach the root vertex.

It is convenient to describe this operation recursively in the other direction, i.e., from the root vertex to the leaf vertices. The construction procedure, if called on a non-leaf vertex, does the following:

1. Recursively construct the values of the two child vertices
2. Merge the computed values of these children.
We start the construction at the root vertex, and hence, we are able to compute the entire segment tree.

The time complexity of this construction is $O(n)$, assuming that the merge operation is constant time (the merge operation gets called n times, which is equal to the number of internal nodes in the segment tree).


### Sum Queries

For now we are going to answer sum queries. As an input we receive two integers l and r, and we have to compute the sum of the segment $a[l…r]$ in $O(logn)$ time.

To do this, we will traverse the Segment Tree and use the precomputed sums of the segments. Let's assume that we are currently at the vertex that covers the segment $a[tl…tr]$. There are three possible cases.

The easiest case is when the segment $a[l…r]$ is equal to the corresponding segment of the current vertex (i.e. $a[l…r]=a[tl…tr]$), then we are finished and can return the precomputed sum that is stored in the vertex.

Alternatively the segment of the query can fall completely into the domain of either the left or the right child. Recall that the left child covers the segment $a[tl…tm]$ and the right vertex covers the segment $a[tm+1…tr]$ with $tm=(tl+tr)/2$. In this case we can simply go to the child vertex, which corresponding segment covers the query segment, and execute the algorithm described here with that vertex.

And then there is the last case, the query segment intersects with both children. In this case we have no other option as to make two recursive calls, one for each child. First we go to the left child, compute a partial answer for this vertex (i.e. the sum of values of the intersection between the segment of the query and the segment of the left child), then go to the right child, compute the partial answer using that vertex, and then combine the answers by adding them. In other words, since the left child represents the segment $a[tl…tm]$ and the right child the segment $a[tm+1…tr]$, we compute the sum query $a[l…tm]$ using the left child, and the sum query $a[tm+1…r]$ using the right child.

So processing a sum query is a function that recursively calls itself once with either the left or the right child (without changing the query boundaries), or twice, once for the left and once for the right child (by splitting the query into two subqueries). And the recursion ends, whenever the boundaries of the current query segment coincides with the boundaries of the segment of the current vertex. In that case the answer will be the precomputed value of the sum of this segment, which is stored in the tree.

In other words, the calculation of the query is a traversal of the tree, which spreads through all necessary branches of the tree, and uses the precomputed sum values of the segments in the tree.

Obviously we will start the traversal from the root vertex of the Segment Tree.

> Complexity: $O(logn)$


### Update Queries

Now we want to modify a specific element in the array, let's say we want to do the assignment $a[i]=x$. And we have to rebuild the Segment Tree, such that it correspond to the new, modified array.

This query is easier than the sum query. Each level of a Segment Tree forms a partition of the array. Therefore an element $a[i]$ only contributes to one segment from each level. Thus only $O(logn)$ vertices need to be updated.

It is easy to see, that the update request can be implemented using a recursive function. The function gets passed the current tree vertex, and it recursively calls itself with one of the two child vertices (the one that contains $a[i]$ in its segment), and after that recomputes its sum value, similar how it is done in the build method (that is as the sum of its two children).


### Implementation

```c++
void build(int node, int start, int end)
{
    if(start == end)
    {
        // Leaf node will have a single element
        tree[node] = A[start];
    }
    else
    {
        int mid = (start + end) / 2;
        // Recurse on the left child
        build(2*node, start, mid);
        // Recurse on the right child
        build(2*node+1, mid+1, end);
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update(int node, int start, int end, int idx, int val)
{
    if(start == end)
    {
        // Leaf node
        A[idx] += val;
        tree[node] += val;
    }
    else
    {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid)
        {
            // If idx is in the left child, recurse on the left child
            update(2*node, start, mid, idx, val);
        }
        else
        {
            // if idx is in the right child, recurse on the right child
            update(2*node+1, mid+1, end, idx, val);
        }
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int sum(int node, int start, int end, int l, int r)
{
    if(r < start or end < l)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if(l <= start and end <= r)
    {
        // range represented by a node is completely inside the given range
        return tree[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}
```

## Practice Problems

[Problem 1](https://codeforces.com/contest/356/problem/A)

[Problem 2](https://codeforces.com/problemset/problem/1234/D)

[Problem 3](https://codeforces.com/contest/474/problem/F)