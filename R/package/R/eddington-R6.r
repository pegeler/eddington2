#' @title An R6 Class for Tracking Eddington Numbers for Cycling
#'
#' @description The class will maintain a running tally, allowing for efficient
#'   updates as new rides come in.
#'
#' @section Warning:
#'
#' A current limitation is that `Eddington` objects cannot be serialized. That
#' is to say, they cannot be carried between sessions using `saveRDS` or `save`
#' and then loaded later using `readRDS` or `load`. Related to this limitation,
#' cloning of `Eddington` objects is disabled.
#'
#' The underlying state is stored as a C++ hash table, which the R session
#' tracks with an external pointer. When attempting to serialize or clone an
#' `Eddington` object, the reference can be lost or corrupted, which will result
#' in undefined behavior. Future versions of this class will address these
#' problems.
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
#' e$current
#'
#' # Update with new data
#' e$update(rep(25, 10))
#'
#' # See the new data
#' e$cumulative
#' @export
Eddington <- R6::R6Class(
  "Eddington",

  # Note cloneable because of XPtr see #4
  # https://github.com/r-lib/R6/issues/178
  # https://github.com/r-lib/R6/issues/179
  cloneable = FALSE,

  public = list(

    #' @description
    #' Create a new Eddington object.
    #' @param rides A vector of rides
    #' @param keep.cumulative logical, indicating whether to keep a vector of
    #'   cumulative Eddington numbers
    #' @return A new `Eddington` object
    initialize = function(rides, keep.cumulative = TRUE) {
      private$.hashmap <- initialize_hashmap()
      if ( !keep.cumulative ) {
        private$.cumulative <- NULL
      }
      if ( !missing(rides) ) {
        self$update(rides)
      }
      },

    #' @description
    #' Print the current Eddington number.
    print = function() {
      cat("Current Eddington Number is:", private$.running, "\n")
      invisible(self)
      },

    #' @description
    #' Add new rides to the existing `Eddington` object.
    #' @param rides A vector of rides
    update = function(rides) {
      result <- update_(rides, private$.running, private$.above, private$.hashmap)
      private$.n            <- private$.n + length(rides)
      private$.running      <- result[["running"]]
      private$.above        <- result[["above"]]
      if ( !is.null(private$.cumulative) )
        private$.cumulative <- c(private$.cumulative, result[["cumulative"]])
      invisible(self)
      },

    #' @description
    #' Get the number of rides of a specified length to get to a target
    #' Eddington number.
    #' @param target Target Eddington number
    #' @return An integer representing the number of rides of target length
    #'   needed to achieve the target number.
    numberToTarget = function(target) {
      if ( target <= private$.running ) {
        return(0L)
      } else if ( target == private$.running + 1L ) {
        return(self$numberToNext)
      } else {
        get_number_to_target(target, private$.hashmap)
      }
      },

    #' @description
    #' Test if an Eddington number is satisfied.
    #' @param target Target Eddington number
    #' @return Logical
    satisfied = function(target) { private$.running >= target }
  ),

  active = list(
    #' @field current The current Eddington number.
    current = function(value) {
      if ( missing(value) ) {
        return(private$.running)
      } else  {
        stop("Data member is read only.", call. = FALSE)
      }
    },

    #' @field cumulative A vector of cumulative Eddington numbers.
    cumulative = function(value) {
      if ( is.null(private$.cumulative) ) {
        stop("Cumulative Eddington Number is not being tracked", call. = FALSE)
      } else if ( missing(value) ) {
        return(private$.cumulative)
      } else  {
        stop("Data member is read only.", call. = FALSE)
      }
    },

    #' @field numberToNext The number of rides needed to get to the next Eddington number.
    numberToNext = function(value) {
      if ( missing(value) ) {
        return(private$.running + 1L - private$.above)
      } else  {
        stop("Data member is read only.", call. = FALSE)
      }
    },

    #' @field n The number of rides in the data.
    n = function(value) {
      if ( missing(value) ) {
        return(private$.n )
      } else  {
        stop("Data member is read only.", call. = FALSE)
      }
    },

    #' @field hashmap The hash map of rides above the current Eddington number.
    hashmap = function(value) {
      if ( missing(value) ) {
        h <- get_hashmap(private$.hashmap)
        h <- h[order(h$lengths),]
        row.names(h) <- NULL
        return(h)
      } else  {
        stop("Data member is read only.", call. = FALSE)
      }
    }
  ),

  private = list(
    .running = 0L,
    .above = 0L,
    .n = 0L,
    .cumulative = integer(0L),
    .hashmap = NULL
  )
)
