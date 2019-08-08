# eddington2
A collection of code for calculating your Eddington Number for cycling.

This repo is a spin-off of a different project where I had the occasion
write a php script for calculating my Eddington number. From there, I have
treated it as a sort of [programming chrestomathy](http://en.wikipedia.org/wiki/Chrestomathy) project *a la* [Rosetta Code](https://rosettacode.org).

## Languages

* C
* php
* python
* R
* VBA (for use in Microsoft Excel)

More to come. Please feel free to contribute!

## The algorithms

There are two basic algorithms used throughout this repo. The first is
one which relies on sorting the data. Although this is fast enough,
there are situations where the sorting operation can be prohibitively 
expensive computationally.

Therefore, I have developed a second algorithm which does not require
initial sorting of the data. Representations of this can be seen in the
`E_cum()` functions defined for python and in the R package.

## R package

The *R/package/* folder is an R package. To install, use `devtools`:

```r
if (!require(devtools)) install.packages("devtools")
devtools::install_github("pegeler/eddington2/R/package")
```

The R package uses Rcpp, which requires a development environment.

