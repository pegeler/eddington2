#include "EddingtonClass.h"
#include <Rcpp.h>

RCPP_MODULE(eddington_mod) {
  using namespace Rcpp;

  class_<Eddington>("EddingtonModule")

  .constructor()
  .constructor<bool>()
  .constructor<IntegerVector, bool>()

  .method("getNumberToNext", &Eddington::getNumberToNext)
  .method("getNumberToTarget", &Eddington::getNumberToTarget)
  .method("isSatisfied", &Eddington::isSatisfied)
  .method("update", &Eddington::update)

  .property("current", &Eddington::getEddingtonNumber)
  .property("cumulative", &Eddington::getCumulativeEddingtonNumber)
  .property("hashmap", &Eddington::getHashmapAsDataframe)
  ;
}
