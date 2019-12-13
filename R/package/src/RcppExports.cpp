// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>
#include <string>
#include <set>

using namespace Rcpp;

// E_num
int E_num(NumericVector& rides);
static SEXP _eddington_E_num_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type rides(ridesSEXP);
    rcpp_result_gen = Rcpp::wrap(E_num(rides));
    return rcpp_result_gen;
END_RCPP_RETURN_ERROR
}
RcppExport SEXP _eddington_E_num(SEXP ridesSEXP) {
    SEXP rcpp_result_gen;
    {
        Rcpp::RNGScope rcpp_rngScope_gen;
        rcpp_result_gen = PROTECT(_eddington_E_num_try(ridesSEXP));
    }
    Rboolean rcpp_isInterrupt_gen = Rf_inherits(rcpp_result_gen, "interrupted-error");
    if (rcpp_isInterrupt_gen) {
        UNPROTECT(1);
        Rf_onintr();
    }
    bool rcpp_isLongjump_gen = Rcpp::internal::isLongjumpSentinel(rcpp_result_gen);
    if (rcpp_isLongjump_gen) {
        Rcpp::internal::resumeJump(rcpp_result_gen);
    }
    Rboolean rcpp_isError_gen = Rf_inherits(rcpp_result_gen, "try-error");
    if (rcpp_isError_gen) {
        SEXP rcpp_msgSEXP_gen = Rf_asChar(rcpp_result_gen);
        UNPROTECT(1);
        Rf_error(CHAR(rcpp_msgSEXP_gen));
    }
    UNPROTECT(1);
    return rcpp_result_gen;
}
// E_cum
IntegerVector E_cum(NumericVector& rides);
static SEXP _eddington_E_cum_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type rides(ridesSEXP);
    rcpp_result_gen = Rcpp::wrap(E_cum(rides));
    return rcpp_result_gen;
END_RCPP_RETURN_ERROR
}
RcppExport SEXP _eddington_E_cum(SEXP ridesSEXP) {
    SEXP rcpp_result_gen;
    {
        Rcpp::RNGScope rcpp_rngScope_gen;
        rcpp_result_gen = PROTECT(_eddington_E_cum_try(ridesSEXP));
    }
    Rboolean rcpp_isInterrupt_gen = Rf_inherits(rcpp_result_gen, "interrupted-error");
    if (rcpp_isInterrupt_gen) {
        UNPROTECT(1);
        Rf_onintr();
    }
    bool rcpp_isLongjump_gen = Rcpp::internal::isLongjumpSentinel(rcpp_result_gen);
    if (rcpp_isLongjump_gen) {
        Rcpp::internal::resumeJump(rcpp_result_gen);
    }
    Rboolean rcpp_isError_gen = Rf_inherits(rcpp_result_gen, "try-error");
    if (rcpp_isError_gen) {
        SEXP rcpp_msgSEXP_gen = Rf_asChar(rcpp_result_gen);
        UNPROTECT(1);
        Rf_error(CHAR(rcpp_msgSEXP_gen));
    }
    UNPROTECT(1);
    return rcpp_result_gen;
}
// E_next
List E_next(NumericVector& rides);
static SEXP _eddington_E_next_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type rides(ridesSEXP);
    rcpp_result_gen = Rcpp::wrap(E_next(rides));
    return rcpp_result_gen;
END_RCPP_RETURN_ERROR
}
RcppExport SEXP _eddington_E_next(SEXP ridesSEXP) {
    SEXP rcpp_result_gen;
    {
        Rcpp::RNGScope rcpp_rngScope_gen;
        rcpp_result_gen = PROTECT(_eddington_E_next_try(ridesSEXP));
    }
    Rboolean rcpp_isInterrupt_gen = Rf_inherits(rcpp_result_gen, "interrupted-error");
    if (rcpp_isInterrupt_gen) {
        UNPROTECT(1);
        Rf_onintr();
    }
    bool rcpp_isLongjump_gen = Rcpp::internal::isLongjumpSentinel(rcpp_result_gen);
    if (rcpp_isLongjump_gen) {
        Rcpp::internal::resumeJump(rcpp_result_gen);
    }
    Rboolean rcpp_isError_gen = Rf_inherits(rcpp_result_gen, "try-error");
    if (rcpp_isError_gen) {
        SEXP rcpp_msgSEXP_gen = Rf_asChar(rcpp_result_gen);
        UNPROTECT(1);
        Rf_error(CHAR(rcpp_msgSEXP_gen));
    }
    UNPROTECT(1);
    return rcpp_result_gen;
}

// validate (ensure exported C++ functions exist before calling them)
static int _eddington_RcppExport_validate(const char* sig) { 
    static std::set<std::string> signatures;
    if (signatures.empty()) {
        signatures.insert("int(*E_num)(NumericVector&)");
        signatures.insert("IntegerVector(*E_cum)(NumericVector&)");
        signatures.insert("List(*E_next)(NumericVector&)");
    }
    return signatures.find(sig) != signatures.end();
}

// registerCCallable (register entry points for exported C++ functions)
RcppExport SEXP _eddington_RcppExport_registerCCallable() { 
    R_RegisterCCallable("eddington", "_eddington_E_num", (DL_FUNC)_eddington_E_num_try);
    R_RegisterCCallable("eddington", "_eddington_E_cum", (DL_FUNC)_eddington_E_cum_try);
    R_RegisterCCallable("eddington", "_eddington_E_next", (DL_FUNC)_eddington_E_next_try);
    R_RegisterCCallable("eddington", "_eddington_RcppExport_validate", (DL_FUNC)_eddington_RcppExport_validate);
    return R_NilValue;
}

static const R_CallMethodDef CallEntries[] = {
    {"_eddington_E_num", (DL_FUNC) &_eddington_E_num, 1},
    {"_eddington_E_cum", (DL_FUNC) &_eddington_E_cum, 1},
    {"_eddington_E_next", (DL_FUNC) &_eddington_E_next, 1},
    {"_eddington_RcppExport_registerCCallable", (DL_FUNC) &_eddington_RcppExport_registerCCallable, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_eddington(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
