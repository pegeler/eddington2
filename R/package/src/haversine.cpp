#include <cmath>
#include <algorithm>

static inline double hav(double theta) {
  return pow(sin(theta / 2), 2);
}

static inline double deg2rad(double deg) {
  return deg * 2 * M_PI / 360;
}

// [[Rcpp::export]]
double get_haversine_distance_(double lat_1,
                               double long_1,
                               double lat_2,
                               double long_2,
                               double r) {
  const double dlat = deg2rad(lat_2 - lat_1);
  const double dlong = deg2rad(long_2 - long_1);
  const double h = hav(dlat) + cos(deg2rad(lat_1)) * cos(deg2rad(lat_2)) * hav(dlong);

  return 2 * r * asin(sqrt(std::clamp(h, 0.0, 1.0)));
}

/*** R
km2mile <- function(km) km / 1.609344
battery_park <- c(40.70089862015537, -74.01520718400144)
red_lighthouse <- c(40.850259693931875, -73.94696203523094)
r_E_km <- 6378.137
r_E_mi <- km2mile(r_E_km)
geosphere::distHaversine(rev(battery_park), rev(red_lighthouse), r = r_E_mi)
geosphere::distVincentySphere(rev(battery_park), rev(red_lighthouse), r = r_E_mi)
do.call(get_haversine_distance, as.list(c(battery_park, red_lighthouse, r_E_mi)))
*/
