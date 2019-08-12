# eddington2
A collection of code for calculating your Eddington number for cycling.

This repo is a spin-off of a different project where I had the occasion to
write a php script for calculating my Eddington number. From there, I have
treated it as a sort of 
[programming chrestomathy](http://en.wikipedia.org/wiki/Chrestomathy) project 
*a la* [Rosetta Code](https://rosettacode.org).

## Languages

* C
* C++
* php
* python
* R
* VBA (for use in Microsoft Excel)

More to come. Please feel free to contribute!

## The algorithms

There are two basic algorithms used throughout this repo. The first, which I
creatively call _algorithm A_, relies on sorting the data. Although this is fast
enough for most use-cases, there are rare situations where the sorting operation
can be too computationally expesive. Also, this is not conducive to calculation
of a cumulative Eddington number, which would otherwise require separate sorting
operations for every new element of the dataset.

Therefore, I have developed a second algorithm (named _algorithm B_) which does 
not require initial sorting of the data. As such, it computes the value in
linear time. This is trivial for small datasets but can have a huge impact on
larger datasets. 

It is also worth noting that with light modifications, it is possible to make
a database schema so that row updates can calculate the new Eddington number in
constant time. At the expense of adding an extra table or a few columns, the E
number for new entries can be computed using a single row that captures the algorithm
state at the previous iteration, rather than using a rider's entire history for
each new row. I am exploring that in the larger project from which this repo is
a spin-off. I will share an example of this as it becomes available.

The two algorithms, A (slow) and B (fast) are shown below in python.

### A (slow)

```python
def E_num(rides) -> int:
    if not rides:
        return 0

    for E, ride in enumerate(sorted(rides, reverse=True), 1):
        if ride < E:
            E -= 1
            break

    return E
```

### B (fast)

```python
def E_num(rides) -> int:

    n, E, above = len(rides), 0, 0
    H = [0 for x in range(n)]

    for i in range(n):
        ride = int(rides[i])

        if ride > E:
            above += 1

            if ride < n:
                H[ride] += 1

            if above > E:
                E += 1
                above -= H[E]

    return E
```

NOTE: The entries in this repo are a mix of algorithms A and B. If both A and B
are present for a given langauage, I append _-deprecated_ to the file name
containing algorithm A.