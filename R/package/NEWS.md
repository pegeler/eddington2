# eddington 4.1.1 (Release date: 2023-12-11)

Changes:

- Adding examples for `read_gpx` and `get_haversine_distance`.

# eddington 4.1.0 (Release date: 2023-11-24)

Changes:

- Supports ingesting GPS Exchange Format (GPX) files. Creates a `data.frame`
  where each row contains the distance of a track segment and date.

# eddington 4.0.1 (Release date: 2023-11-07)

Changes:

- Minimum R version is now 4.3.0 and requires compiler capable of C++17 standard.
- Full re-implementation of C++ code. As a result, memory usage will be reduced
  for typical datasets.
- Introduction of `EddingtonModule` Rcpp module. This class maintains algorithm
  state, and so can be updated multiple times as new data comes in.
- Introduction of `Eddington` R6 class. This provides similar functionality to
  the `EddingtonModule` Rcpp module. All methods are implemented in pure R. It
  uses R's new `hashtab` data structure, which is experimental as of this
  package release.

# eddington 2.1.2 (Release date: 2020-03-24)

Changes:

- Further refinement of documentation.

# eddington 2.1.1 (Release date: 2020-03-21)

**First CRAN release**

Changes:

- Improved documentation.

# eddington 2.1.0 (Release date: 2019-10-20)

Changes:

- Added `rides` simulated dataset.
- Added a vignette.

# eddington 2.0.0 (Release date: 2019-08-24)

Changes:

- Functionality of `E_req()` has been migrated to `E_next()`
- `E_req()` now takes a candidate mileage and returns number of rides required to achieve that _E_.

# eddington 1.0.0 (Release date: 2018-12-17)

Changes:

- R version of `Eddington_number` and c++ `E_fast` are now defunct.
- `E_num` is now the method for getting the single maximum Eddington number of a dataset.
- Added `E_sat` that checks to see if a dataset satisfies a certain Eddington number.
- Added `E_req` that determines the minimum number of rides to increment Eddington number.

# eddington 0.1.1 (Release date: 2018-12-15)

Changes:

- Removed c++11 and other dependencies in c++ code.

# eddington 0.1.0 (Release date: 2018-12-02)

Changes:

- Added cumulative function, `E_cum`.

# eddington 0.0.0 (Release date: 2018-11-27)

Changes:

- Initial release
