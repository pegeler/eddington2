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
#' @importFrom R6 R6Class
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
      if (!keep.cumulative)
        private$.cumulative <- NULL
      if (!missing(rides))
        self$update(rides)
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
        private$.n <- private$.n + length(rides)
        rides <- as.integer(rides)
        if (!is.null(private$.cumulative)) {
          cumulative <- integer(length(rides))
        }

        for (i in seq_along(rides)) {
          ride <- rides[i]

          if (ride > private$.running) {
            private$.above <- private$.above + 1L
            private$.incrementHashmap(ride)

          if (private$.above > private$.running) {
            private$.running <- private$.running + 1L;
            n_at_dist <- private$.hashmap[[private$.running, 0L]]
            private$.above <- private$.above - n_at_dist
            remhash(private$.hashmap, private$.running);
          }
        }

        if (!is.null(private$.cumulative)) {
          cumulative[i] <- private$.running
        }
      }
      if (!is.null(private$.cumulative)) {
        private$.cumulative <- c(private$.cumulative, cumulative)
      }
      invisible(self)
    },

    #' @description
    #' Get the number of rides of a specified length to get to a target
    #' Eddington number.
    #' @param target Target Eddington number
    #' @return An integer representing the number of rides of target length
    #'   needed to achieve the target number.
    getNumberToTarget = function(target) {
      if (target <= private$.running)
        return(0L)
      if (target == private$.running + 1L)
        return(self$getNumberToNext)
      n_above <- 0L
      maphash(
        private$.hashmap,
        \(k, v) if (k >= target) n_above <<- n_above + v
      )
      target - n_above
    },

    #' @description
    #' Test if an Eddington number is satisfied.
    #' @param target Target Eddington number
    #' @return Logical
    isSatisfied = function(target) private$.running >= target
  ),

  active = list(
    #' @field current The current Eddington number.
    current = function(value) {
      if (!missing(value))
        stop("Data member is read only.", call. = FALSE)
      private$.running
    },

    #' @field cumulative A vector of cumulative Eddington numbers.
    cumulative = function(value) {
      if (is.null(private$.cumulative))
        stop("Cumulative Eddington Number is not being tracked", call. = FALSE)
      if (!missing(value))
        stop("Data member is read only.", call. = FALSE)
      private$.cumulative
    },

    #' @field getNumberToNext The number of rides needed to get to the next
    #'  Eddington number.
    getNumberToNext = function(value) {
      if (!missing(value))
        stop("Data member is read only.", call. = FALSE)
      private$.running + 1L - private$.above
    },

    #' @field n The number of rides in the data.
    n = function(value) {
      if (!missing(value))
        stop("Data member is read only.", call. = FALSE)
      private$.n
    },

    #' @field hashmap The hash map of rides above the current Eddington number.
    hashmap = function(value) {
      if (!missing(value))
        stop("Data member is read only.", call. = FALSE)
      nkeys <- numhash(private$.hashmap)
      i <- 1L
      lengths <- integer(nkeys)
      counts <- integer(nkeys)
      maphash(
        private$.hashmap,
        \(k, v) {
          lengths[i] <<- k
          counts[i] <<- v
          i <<- i + 1L
        }
      )
      h <- data.frame("length" = lengths, "count" = counts)
      h <- h[order(h$length),]
      h
    }
  ),

  private = list(
    .running = 0L,
    .above = 0L,
    .n = 0L,
    .cumulative = integer(0L),
    .hashmap = hashtab(size = 150L),

    .incrementHashmap = function(ride) {
      old <- private$.hashmap[[ride, 0L]]
      private$.hashmap[[ride]] <- old + 1L
    }
  )
)
