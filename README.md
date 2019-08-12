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
can be too computationally expensive. Also, this is not conducive to calculation
of a cumulative Eddington number, which would otherwise require separate sorting
operations for every new element of the dataset.

Therefore, I have developed a second algorithm (named _algorithm B_) which does 
not require initial sorting of the data. As such, it computes the value in
linear time. This is trivial for small datasets but can have a huge impact on
larger datasets. 

Several of the entries contain algorithm B. If you are using any of this code in
production, I would check that the particular function definition you are using
is algorithm B. If not, there is probably another file in the folder which does
contain algorithm B. (**Also, please note that this is licensed under GPL-3 so I
make no claims nor warranty of any kind, including with regard to the fitness of
this code in a production context---do your own testing!**)

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
