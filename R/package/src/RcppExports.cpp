// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/eddington.h"
#include <Rcpp.h>
#include <string>
#include <set>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// E_num
int E_num(const Rcpp::IntegerVector& rides);
static SEXP _eddington_E_num_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type rides(ridesSEXP);
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
Rcpp::IntegerVector E_cum(const Rcpp::IntegerVector& rides);
static SEXP _eddington_E_cum_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type rides(ridesSEXP);
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
Rcpp::List E_next(const Rcpp::IntegerVector& rides);
static SEXP _eddington_E_next_try(SEXP ridesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type rides(ridesSEXP);
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
        signatures.insert("int(*E_num)(const Rcpp::IntegerVector&)");
        signatures.insert("Rcpp::IntegerVector(*E_cum)(const Rcpp::IntegerVector&)");
        signatures.insert("Rcpp::List(*E_next)(const Rcpp::IntegerVector&)");
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

RcppExport SEXP _rcpp_module_boot_eddington_mod();

static const R_CallMethodDef CallEntries[] = {
    {"_eddington_E_num", (DL_FUNC) &_eddington_E_num, 1},
    {"_eddington_E_cum", (DL_FUNC) &_eddington_E_cum, 1},
    {"_eddington_E_next", (DL_FUNC) &_eddington_E_next, 1},
    {"_rcpp_module_boot_eddington_mod", (DL_FUNC) &_rcpp_module_boot_eddington_mod, 0},
    {"_eddington_RcppExport_registerCCallable", (DL_FUNC) &_eddington_RcppExport_registerCCallable, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_eddington(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
