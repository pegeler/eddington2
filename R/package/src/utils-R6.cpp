#include <Rcpp.h>
#include <unordered_map>

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
XPtr< std::unordered_map<int, int> > initialize_hashmap() {
  std::unordered_map<int, int>* umap = new std::unordered_map<int, int>(150);
  XPtr< std::unordered_map<int, int> > p(umap, true);
  return p;
}

// [[Rcpp::export]]
List internal_update(
    NumericVector rides,
    int running,
    int above,
    XPtr< std::unordered_map<int, int> > H)
{
  int ride=0;
  IntegerVector cumulative( rides.size() );

  for ( int i=0; i < rides.size(); i++ )
  {
    ride = (int) rides[i];

    if ( ride > running ) {
      above++;
      (*H)[ride]++;

      if ( above > running ) {
        running++;
        above -= (*H)[running];
        H->erase(running);
      }
    }
    cumulative[i] = running;
  }

  return List::create(
    _["running"]    = running,
    _["above"]      = above,
    _["cumulative"] = cumulative);
}

// [[Rcpp::export]]
int internal_n2target(
    int target,
    XPtr< std::unordered_map<int, int> > H)
{
  int completed_rides = 0;
  for ( auto it = H->begin(); it != H->end(); ++it )
    if ( it->first >= target )
      completed_rides += it->second;
  return target - completed_rides;
}

// [[Rcpp::export]]
DataFrame internal_get_hashmap(
    XPtr< std::unordered_map<int, int> > H)
{
  IntegerVector ride_len, ride_count;
  for ( auto it = H->begin(); it != H->end(); ++it ) {
    ride_len.push_back(it->first);
    ride_count.push_back(it->second);
  }
  return DataFrame::create(
    _["ride_length"] = ride_len,
    _["ride_count"] = ride_count
  );
}

/*** R
rides <- rgamma(15, shape = 2, scale = 10)
running <- above <- 0L
H <- initialize_hashmap()
internal_update(rides, running, above, H)
*/
