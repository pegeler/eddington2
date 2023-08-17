// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#ifndef RCPP_eddington_RCPPEXPORTS_H_GEN_
#define RCPP_eddington_RCPPEXPORTS_H_GEN_

#include <Rcpp.h>

namespace eddington {

    using namespace Rcpp;

    namespace {
        void validateSignature(const char* sig) {
            Rcpp::Function require = Rcpp::Environment::base_env()["require"];
            require("eddington", Rcpp::Named("quietly") = true);
            typedef int(*Ptr_validate)(const char*);
            static Ptr_validate p_validate = (Ptr_validate)
                R_GetCCallable("eddington", "_eddington_RcppExport_validate");
            if (!p_validate(sig)) {
                throw Rcpp::function_not_exported(
                    "C++ function with signature '" + std::string(sig) + "' not found in eddington");
            }
        }
    }

    inline int E_num(const IntegerVector& rides) {
        typedef SEXP(*Ptr_E_num)(SEXP);
        static Ptr_E_num p_E_num = NULL;
        if (p_E_num == NULL) {
            validateSignature("int(*E_num)(const IntegerVector&)");
            p_E_num = (Ptr_E_num)R_GetCCallable("eddington", "_eddington_E_num");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_E_num(Shield<SEXP>(Rcpp::wrap(rides)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<int >(rcpp_result_gen);
    }

    inline IntegerVector E_cum(const IntegerVector& rides) {
        typedef SEXP(*Ptr_E_cum)(SEXP);
        static Ptr_E_cum p_E_cum = NULL;
        if (p_E_cum == NULL) {
            validateSignature("IntegerVector(*E_cum)(const IntegerVector&)");
            p_E_cum = (Ptr_E_cum)R_GetCCallable("eddington", "_eddington_E_cum");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_E_cum(Shield<SEXP>(Rcpp::wrap(rides)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<IntegerVector >(rcpp_result_gen);
    }

    inline List E_next(const IntegerVector& rides) {
        typedef SEXP(*Ptr_E_next)(SEXP);
        static Ptr_E_next p_E_next = NULL;
        if (p_E_next == NULL) {
            validateSignature("List(*E_next)(const IntegerVector&)");
            p_E_next = (Ptr_E_next)R_GetCCallable("eddington", "_eddington_E_next");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_E_next(Shield<SEXP>(Rcpp::wrap(rides)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<List >(rcpp_result_gen);
    }

}

#endif // RCPP_eddington_RCPPEXPORTS_H_GEN_
