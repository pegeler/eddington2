# eddington2

A collection of code for calculating your
[Eddington number for cycling](https://en.wikipedia.org/wiki/Arthur_Eddington#Eddington_number_for_cycling).
This will also calculate an author's [_h_-index](https://en.wikipedia.org/wiki/H-index),
which is mathematically equivalent but applied to a different field of interest.
Both of these numbers are specific applications of computing the side length of a
[Durfee square](https://en.wikipedia.org/wiki/Durfee_square).

This repo is a spin-off of a different project where I had the occasion to
write a php script for calculating my Eddington number. From there, I have
treated it as a sort of 
[programming chrestomathy](http://en.wikipedia.org/wiki/Chrestomathy) project 
*a la* [Rosetta Code](https://rosettacode.org).

If you're here because you just need a quick way to calculate your Eddington
number, check out the online calculator
[here](https://pegeler.github.io/eddington2/).

## Table of contents

* [Languages](#languages)
* [The algorithms](#the-algorithms)
    * [Time and space complexity](#time-and-space-complexity)
    * [Improvement over sorting](#improvement-over-sorting)
    * [Variations and applications](#variations-and-applications)
* [Deprecation](#deprecation)

## Languages

* [GNU APL](apl/)
* [awk](awk/)
* [bash](bash/)
* [C](c/)
* [C++](cpp/)
* [FORTRAN 90](fortran/)
* [Java](java/)
* [Javascript](docs/)
* [Julia](julia/)
* [MySQL](mysql/)
* [Perl 5](perl/)
* [PHP](php/)
* [Python](python/)
* [R](R/)
* [Rcpp](R/)
* [Rust](rust/)
* [SAS](sas/)
* [Scala](scala/)
* [Apache Spark](spark/)
* [VBA](vba/) (for use in Microsoft Excel)

More to come. Please feel free to contribute!

## The algorithms

The algorithms used throughout this repo fall into two general categories. The
first, which I creatively call **Algorithm A**, relies on sorting the data.
Although this is fast enough for most use-cases, there are rare situations where
the sorting operation can be too computationally expensive. Also, this is not
conducive to calculation of a cumulative Eddington number, which would require
separate sorting operations for every new element of the dataset. This is
trivial for small datasets but can have a huge impact on larger datasets.

Therefore, I have developed a second algorithm (named **Algorithm B**) which
does not require initial sorting of the data. The algorithm goes through the
data only once, keeping a running tally of E, and computing the summary value in
linear time. Since a running E is calculated as the algorithm iterates over the
data, it is an efficient way of computing the cumulative E.

The two algorithms, **A** (slow) and **B** (fast) are shown below in python.

**A (slow)**

```python
def E_num(rides):
    if not rides:
        return 0

    for E, ride in enumerate(sorted(rides, reverse=True), 1):
        if ride < E:
            E -= 1
            break

    return E
```

**B (fast)**

```python
def E_num(rides):

    n, E, above = len(rides), 0, 0
    H = [0]*(n + 1)

    for r in rides:
        ride = int(r)
        if ride > E:
            above += 1
            if ride < n:
                H[ride] += 1
            if above > E:
                E += 1
                above -= H[E]

    return E
```

### Time and space complexity

**Algorithm B** is generally faster than the conventional approach, which uses a
comparison sort (as illustrated in **Algorithm A**), even when used just for
summary statistics. Whereas we would expect **Algorithm A** to complete in 
O(n&nbsp;log&nbsp;n) asymptotic time, **Algorithm B** has &theta;(n) time
complexity and uses &theta;(n) auxiliary space. This is accomplished through
exploiting three constraints peculiar to the metric:

1. Inputs are integers or can be truncated to be so.
1. A tally (histogram) of past data suffices to track the necessary state
information. Elements of the tally can be accessed in constant time when needed.
1. We know in advance the required auxiliary space is at most n.

### Improvement over sorting

The next obvious improvement over using comparison sort would have been an
integer sorting algorithm such as counting sort. In fact, **Algorithm B** is
very comparable to, but a little faster than, counting sort. They both use a
tally. Compared to most comparison sorting algorithms' expected
O(n&nbsp;log&nbsp;n) time complexity and **Algorithm B**'s &theta;(n), counting
sort falls in between the two with O(n&nbsp;+&nbsp;k) asymptotic time
complexity, where k is the range of the input vector. As a bonus, k will be
sufficiently small as to be meaningless in real-world cycling data. But there
are some considerations to review. In pathological cases, a large k can be
problematic. Also, counting sort tends to iterate through the data several
times, meaning that it could be a couple of factors slower for any given n.

For summary statistics, using a counting sort algorthim is practically
equivalent to **Algorithm B** with respect to speed and efficiency. But that is
not the whole story: **Algorithm B** is remarkable because of how it handles
cumulative statistics. Neither out-of-the-box comparison sort nor counting sort
facilitate efficient computation of the cumulative statistic since previous
effort of sorting is not conserved as the we iterate through the growing vector
of data. As a result, time complexity grows to &#8721;O(n&nbsp;+&nbsp;k) for
counting sort, which approximately reduces to O(n^2) if we ignore k. Of course,
using comparison sort would be much worse! Meanwhile, **Algorithm B** remains
&theta;(n)---this is where the true value of **Algorithm B** lies.

#### Disclaimer

When speaking of sorting algorithms, I am speaking in generalities. Many
sorting algorithms may be exceptions to certain rules. But when all things are
considered, the overall thrust is that **Algorithm B** is still an improvement
over all other approaches because it uses specific information about the output
metric to eliminate unnecessary computations.

### Variations and applications

Although **Algorithm B** is shown above with a simple Python list serving as the
histogram, other data structures were considered. Either a binary tree or
hashmap could be used as a subsitute.

If space complexity is an issue, they may be preferable. However, my findings
are that the overhead of implementing the algorithm with a more complex data
structure results in a slower overall runtime. Meanwhile, space concerns are
not relevant with most "realistic" datasets.

There are still other reasons a binary tree or hashmap may be considered. Either
data structure facilitates the transformation of this algorithm into an
[online algorithm](https://en.wikipedia.org/wiki/Online_algorithm), meaning
inputs can be streamed into the algorithm without prior knowledge of the data
length. Although it is unlikely that an online algorithm will be necessary to
process a cyclist's Eddington number or an author's h-index, this may be used
for computing the side length of a Durfee square for partitions of large
integers or be used in some yet undiscovered application.

Using binary trees or hashmaps also presents new opportunities for OOP with
Eddington numbers. The classes defined in the [Python](python/) and [C++](cpp/)
folders illustrate this. One benefit is that a class can be instantiated with
an initial dataset and then updated with more data at a later time.

It also is possible to make a database schema so that row insertions can
calculate the new Eddington number in constant time. At the expense of adding an
extra table and a few columns, the E number for new entries can be computed
using a single row that captures the algorithm state at the previous iteration,
rather than using a rider's entire history for each new row. This has the
potential to provide benefit to fitness tracking software backends, where scale
is relevant.

## Deprecation

The entries in this repo are a mix of **Algorithms A** and **B**. If both **A**
and **B** are present for a given langauage, I append _`-deprecated`_ to the
file name containing **Algorithm A**.
