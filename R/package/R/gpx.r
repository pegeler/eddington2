NAMESPACES <- c(d = "http://www.topografix.com/GPX/1/1")
TIMESTAMP_FORMAT <- "%FT%T.000Z"

#' Compute the distance between two points using the Haversine formula
#'
#' Uses the Haversine great-circle distance formula to compute the distance
#' between two latitude/longitude points.
#'
#' @param lat_1,lon_1,lat_2,lon_2 The coordinates
#'    used to compute the distance.
#' @param units The units of the output distance.
#' @examples
#' # In NYC, 20 blocks == 1 mile. Thus, computing the distance between two
#' # points along 7th Ave from W 39 St to W 59 St should return ~1 mile.
#' w39_coords <- list(lat=40.75406905512651, lon=-73.98830604245481)
#' w59_coords <- list(lat=40.76684156255418, lon=-73.97908243833855)
#'
#' get_haversine_distance(
#'   w39_coords$lat,
#'   w39_coords$lon,
#'   w59_coords$lat,
#'   w59_coords$lon,
#'   "miles"
#' )
#'
#' # The total distance along a sequence of points can be computed. Consider the
#' # following sequence of points along Park Ave in the form of a list of points
#' # where each point is a list containing a `lat` and `lon` tag.
#' park_ave_coords <- list(
#'   list(lat=40.735337983655434, lon=-73.98973648773142),  # E 15 St
#'   list(lat=40.74772623378332, lon=-73.98066078090876),   # E 35 St
#'   list(lat=40.76026319186414, lon=-73.97149360922498),   # E 55 St
#'   list(lat=40.77301604875587, lon=-73.96217737679450)    # E 75 St
#' )
#'
#' # We can create a function to compute the total distance as follows:
#' compute_total_distance <- function(coords) {
#'   sum(
#'     sapply(
#'       seq_along(coords)[-1],
#'       \(i) get_haversine_distance(
#'         coords[[i]]$lat,
#'         coords[[i]]$lon,
#'         coords[[i - 1]]$lat,
#'         coords[[i - 1]]$lon,
#'         "miles"
#'       )
#'     )
#'   )
#' }
#'
#' # Then applying the function to our sequence results in a total distance.
#' compute_total_distance(park_ave_coords)
#' @returns The distance between two points in the requested units.
#' @references <https://en.wikipedia.org/wiki/Haversine_formula>
#' @export
get_haversine_distance <- function(lat_1,
                                   lon_1,
                                   lat_2,
                                   lon_2,
                                   units = c("miles", "kilometers")) {
  r <- switch(match.arg(units), miles = R_E_MI, kilometers = R_E_KM)
  .Call(`_eddington_get_haversine_distance_`, lat_1, lon_1, lat_2, lon_2, r)
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
#' @examples
#' \dontrun{
#' # Get a list of all GPX export files in a directory tree
#' gpx_export_files <- list.files(
#'   "/path/to/gpx/exports/",
#'   pattern = "\\.gpx$",
#'   full.names = TRUE,
#'   recursive = TRUE
#' )
#'
#' # Read in all files and combine them into a single data frame
#' rides <- do.call(rbind, lapply(gpx_export_files, read_gpx))
#' }
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
