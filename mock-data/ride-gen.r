#!/usr/bin/env Rscript
set.seed(2018)
x <- rgamma(100, shape = 2, scale = 10)
cat(formatC(x, format = "f", digits = 2L), file = "rides.dat", sep = "\n")
cat(eddington::E_cum(x), file = "E_expected.dat", sep = "\n")

