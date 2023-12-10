NAMESPACES <- c(d = "http://www.topografix.com/GPX/1/1")
TIMESTAMP_FORMAT <- "%FT%T.000Z"

#' Compute the distance between two points using the Haversine formula
#'
#' Uses the Haversine great-circle distance formula to compute the distance
#' between two latitude/longitude points.
#'
#' @param lat_1,long_1,lat_2,long_2 The coordinates
#'    used to compute the distance.
#' @param units The units of the output distance.
#' @returns The distance between two points in the requested units.
#' @references <https://en.wikipedia.org/wiki/Haversine_formula>
#' @export
get_haversine_distance <- function(lat_1,
                                   long_1,
                                   lat_2,
                                   long_2,
                                   units = c("miles", "kilometers")) {
  r <- switch(match.arg(units), miles = R_E_MI, kilometers = R_E_KM)
  .Call(`_eddington_get_haversine_distance_`, lat_1, long_1, lat_2, long_2, r)
}

#' Read a GPX file into a data frame containing dates and distances
#'
#' Reads in a GPS Exchange Format XML document and outputs a `data.frame`
#' containing distances. The corresponding dates for each track segment
#' (`trkseg`) will be included if present in the source file, else the `date`
#' column will be populated with `NA`s.
#'
#' Distances are computed using the Haversine formula and do not account for
#' elevation changes.
#'
#' This function treats the first timestamp of each `trkseg` as the date of
#' record. Thus overnight track segments will all count toward the day in which
#' the journey began.
#'
#' @param file The input file to be parsed.
#' @param units The units desired for the distance metric.
#' @returns A data frame containing up to two columns:
#'  \describe{
#'    \item{date}{The date of the ride. See description and details.}
#'    \item{distance}{The distance of the track segment in the requested units.}
#'  }
#' @export
read_gpx <- function(file, units = c("miles", "kilometers")) {
  x <- XML::xmlInternalTreeParse(file)
  on.exit(XML::free(x))

  distances <- get_trkseg_dist(x, match.arg(units))

  if (!length(distances)) {
    # No trkseg nodes were found. Returning an empty data frame
    return(
      data.frame(
        date = double(0L),
        distance = double(0L)
      )
    )
  }

  dates <- get_dates(x)

  data.frame(
    # do.call preserves "Date" class
    date = if (length(dates) == length(distances)) do.call(c, dates) else as.Date(NA),
    distance = unlist(distances)
  )
}

# XML parsing helper functions --------------------------------------------

get_dates <- function(x) {
  timestamps <- XML::xpathApply(
    x,
    "//d:trkseg/d:trkpt[1]/d:time",
    XML::xmlValue,
    namespaces = NAMESPACES
  )
  lapply(timestamps, as.Date, TIMESTAMP_FORMAT)
}

get_trkseg_dist <- function(x, units = c("miles", "kilometers")) {
  r <- switch(match.arg(units), miles = R_E_MI, kilometers = R_E_KM)

  lapply(
    XML::getNodeSet(x, "//d:trkseg", namespaces = NAMESPACES),
    \(trkseg) {
      trkpts <- XML::xmlChildren(trkseg)
      if (length(trkpts) < 2) return(0.)
      Reduce(
        `+`,
        apply(
          cbind(trkpts[-1], trkpts[-length(trkpts)]),
          1,
          \(pair) .Call(`_eddington_get_haversine_distance_`,
            as.double(XML::xmlGetAttr(pair[[1]], "lat")),
            as.double(XML::xmlGetAttr(pair[[1]], "lon")),
            as.double(XML::xmlGetAttr(pair[[2]], "lat")),
            as.double(XML::xmlGetAttr(pair[[2]], "lon")),
            r
          )
        )
      )
    })
}

# Unused ------------------------------------------------------------------

get_trkseg_coords <- function(x) {
  trksegs <- lapply(
    XML::getNodeSet(x, "//d:trkseg", namespaces = NAMESPACES),
    \(trkseg) XML::xmlApply(
      trkseg,
      \(trkpt) as.double(c(XML::xmlGetAttr(trkpt, "lat"),
                           XML::xmlGetAttr(trkpt, "lon")))
    )
  )
  lapply(
    trksegs,
    \(trkseg) stats::setNames(
      as.data.frame(
        do.call(rbind, trkseg),
        row.names = FALSE),
      c("lat", "lon")
    )
  )
}
