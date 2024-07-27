#' An R6 Class for Tracking Eddington Numbers for Cycling
#'
#' @description
#' The class will maintain the state of the algorithm, allowing for efficient
#' updates as new rides come in.
#'
#' @section Warnings:
#'
#' The implementation uses an experimental base R feature [utils::hashtab].
#'
#' Cloning of `Eddington` objects is disabled. Additionally, `Eddington` objects
#' cannot be serialized; they cannot be carried between sessions using
#' [base::saveRDS] or [base::save] and then loaded later using [base::readRDS]
#' or [base::load].
#'
#' @examples
#' # Randomly generate a set of 15 rides
#' rides <- rgamma(15, shape = 2, scale = 10)
#'
#' # View the rides sorted in decreasing order
#' stats::setNames(sort(rides, decreasing = TRUE), seq_along(rides))
#'
#' # Create the Eddington object
#' e <- Eddington$new(rides, store.cumulative = TRUE)
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

  # Not cloneable because it will not make a deep copy of the `hashtab` object.
  cloneable = FALSE,

  public = list(

    #' @description
    #' Create a new Eddington object.
    #' @param rides A vector of rides
    #' @param store.cumulative logical, indicating whether to keep a vector of
    #'   cumulative Eddington numbers
    #' @return A new `Eddington` object
    initialize = function(rides, store.cumulative = FALSE) {
      private$.hashmap <- hashtab(size = 150L)
      if (store.cumulative)
        private$.cumulative <- integer(0L)
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
              private$.running <- private$.running + 1L
              n_above_at_dist <- gethash(private$.hashmap, private$.running, 0L)
              private$.above <- private$.above - n_above_at_dist
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
        return(self$number_to_next)
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

    #' @field number_to_next The number of rides needed to get to the next
    #'  Eddington number.
    number_to_next = function(value) {
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
      h[order(h$length),]
    }
  ),

  private = list(
    .running = 0L,
    .above = 0L,
    .n = 0L,
    .cumulative = NULL,
    .hashmap = NULL,

    .incrementHashmap = function(ride) {
      old <- gethash(private$.hashmap, ride, 0L)
      sethash(private$.hashmap, ride, old + 1L)
    }
  )
)
