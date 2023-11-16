# Source: https://www.nist.gov/pml/special-publication-811/nist-guide-si-appendix-b-conversion-factors/nist-guide-si-appendix-b8
MILES_PER_KM <- 1.609344

# Source: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
R_E_KM <- 6378.137
R_E_MI <- R_E_KM / MILES_PER_KM

usethis::use_data(
  MILES_PER_KM,
  R_E_KM,
  R_E_MI,
  overwrite = TRUE,
  internal = TRUE
)
