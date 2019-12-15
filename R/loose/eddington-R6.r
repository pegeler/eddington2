library(hashmap)
library(R6)

#' An R6 Class for Tracking Eddington Numbers for Cycling
#'
#' The class will maintain a running tally, allowing for efficient updates
#' as new rides come in.
#'
#' @examples
#' # Randomly generate a set of 15 rides
#' rides <- rgamma(15, shape = 2, scale = 10)
#'
#' # View the rides sorted in decreasing order
#' setNames(sort(rides, decreasing = TRUE), seq_along(rides))
#'
#' # Create the Eddington object
#' e <- Eddington$new(rides)
#'
#' # Get the Eddington number
#' e$current(rides)
#'
#' # Update with new data
#' e$update(rep(25, 10))
#'
#' # See the new data
#' e$cumulative
#' @export
Eddington <- R6::R6Class(
  "Eddington",
  public = list(

    #' @description
    #' Create a new Eddington object.
    #' @param rides A vector of rides
    #' @return A new `Eddington` object
    initialize = function(rides){
      if ( !missing(rides) ) self$update(rides)
      },

    print = function(){
      cat("Current Eddington Number is:", private$.running, "\n")
      invisible(self)
      },

    #' @description
    #' Add new rides to the existing `Eddington` object.
    #' @param rides A vector of rides
    update = function(rides){
      tmp_vec <- integer(length(rides))
      for ( i in seq_along(rides) ) {
        ride <- as.integer(rides[i])
        if ( ride > private$.running ) {
          private$.above <- private$.above + 1L
          private$.incr_H(ride)

          if ( private$.above > private$.running ) {
            private$.running <- private$.running + 1L
            private$.decr_H(private$.running)
          }
        }
        tmp_vec[i] <- private$.running
      }
      private$.cumulative <- c(private$.cumulative, tmp_vec)
      invisible(self)
      },

    #' @description
    #' Get the number of rides of a specified length to get to a target
    #' Eddington number.
    #' @param target Target Eddington number
    #' @return An integer representing the number of rides of target length
    #'   needed to achieve the target number.
    n2target = function(target){
      if ( target <= private$.running ) {
        return(0L)
      } else if ( target == private$.running + 1L ) {
        return(self$n2next)
      } else {
        keys <- private$.H$keys()
        target - sum(private$.H$find(keys[keys >= target]))
      }
      },

    #' @description
    #' Test if an Eddington number is satisfied.
    #' @param target Target Eddington number
    #' @return Logical
    satisfied = function(target){ private$.running >= target }
  ),
  active = list(
    #' @field The current Eddington number.
    current = function(){ private$.running },

    #' @field A vector of cumulative Eddington numbers.
    cumulative = function(){ private$.cumulative },

    #' @field The number of rides needed to get to the next Eddington number.
    n2next = function(){ private$.running + 1L - private$.above },

    #' @field The number of rides in the data.
    n = function(){ length(private$.cumulative) }
  ),
  private = list(
    .running = 0L,
    .above = 0L,
    .cumulative = integer(0L),
    .H = hashmap(1:200, rep(0L, 200)),
    .incr_H = function(key) {
      private$.H[[key]] <- 1L +
        if ( private$.H$has_key(key) ) private$.H[[key]] else 0L

      },
    .decr_H = function(key, erase = TRUE) {
      if ( private$.H$has_key(key) ) {
        private$.above <- private$.above - private$.H[[key]]
        if ( erase ) private$.H$erase(key)
        }
      }
  )
)
