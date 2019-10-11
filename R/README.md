# R

## Folder contents

### _loose/_

These are loose scripts not connected with the package. The _eddington.r_ file
may be useful in that it calculates the Eddington number in pure R. Therefore,
you do not need a development environment to use it, unlike the R package in the
other folder.

If you have a development environment and want faster code, I recommend installing 
and using the R package rather than these loose scripts. Especially because the
Rcpp version in this folder uses the slower algorithm, whereas the R package
uses the optimized Rcpp code and is much faster.

### _package/_

[![Travis-CI Build Status](https://travis-ci.org/pegeler/eddington2.svg?branch=master)](https://travis-ci.org/pegeler/eddington2)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/pegeler/eddington2?branch=master&svg=true)](https://ci.appveyor.com/project/pegeler/eddington2)


This folder is an R package. To install, use `devtools`:

```r
if (!require(devtools)) install.packages("devtools")
devtools::install_github("pegeler/eddington2/R/package")
```

NOTE: This package uses Rcpp and so needs a development environment. If you do
not have a development environment and want to calculate an Eddington number,
use the [_eddington.r_](loose/eddington.r) script in _loose/_. This computes the
number using base R.

## Microbenchmarking

Here I'm comparing the optimized Rcpp code used in the package (`E_num()`) with
the base R code found in the loose scripts folder (`Eddington_number()`) using
[microbenchmark](https://github.com/joshuaulrich/microbenchmark/). The dataset
is the [mock data](../mock-data) found in this repo.


```r
library(microbenchmark)
rides <- as.numeric(readLines("../mock-data/rides.dat"))
microbenchmark(E_num(rides), Eddington_number(rides))
```

```r
## Unit: microseconds
##                     expr     min       lq      mean  median      uq     max neval cld
##             E_num(rides)   4.737   5.3665   6.88629   7.349   7.707  17.760   100  a 
##  Eddington_number(rides) 100.293 101.8555 105.97427 103.186 105.504 277.938   100   b
```


You can see that the difference in median times is about 96 microseconds on my
machine, or a factor of 14.

I was inspired to create the new algorithm because of my interest in computing
a cumulative Eddington number on larger datasets. Let's define a cumulative
Eddington number in base R, called `E_cumR()` and compare it to the `E_cum()`
function included in the package.

```r
E_cumR <- function(rides) {
  sapply(seq_along(rides), function(i) Eddington_number(rides[seq_len(i)])
}

microbenchmark(E_cum(rides), E_cumR(rides))
```

```r
## Unit: microseconds
##           expr      min       lq        mean    median        uq       max neval cld
##   E_cum(rides)    4.802    5.742    13.30837   16.8805    19.151    42.317   100  a 
##  E_cumR(rides) 9783.453 9861.086 10471.62408 9903.3595 10095.600 19901.871   100   b
```

You can see that the median time is now 587x faster using the package code over
our function defined in base R. That said, 587x faster is still the difference 
of 9900 microseconds over 100 rides. So really in most cases, it's just as good
to use the R code if there is a level of convenience associated with it. In fact,
the time taken to type this sentence is probably more than all the time savings
I'll ever realize by developing the better algorithm!
