# TODO:
#   - Give units arg to `read_gpx` and `haversine`
#   - Document (and possibly export) functions here
#   - Write the vignette

NAMESPACES <- c(d = "http://www.topografix.com/GPX/1/1")
TIMESTAMP_FORMAT <- "%FT%T.000Z"

get_dates <- function(x) {
  # We're treating the fist timestamp of each trkseg as the date of record

  timestamps <- XML::xpathApply(
    x,
    "//d:trkseg/d:trkpt[1]/d:time",
    XML::xmlValue,
    namespaces = NAMESPACES
  )
  lapply(timestamps, as.Date, TIMESTAMP_FORMAT)
}

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

get_trkseg_dist <- function(x, r) {
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
          \(pair) get_haversine_distance(
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

#' @export
read_gpx <- function(file, units = c("miles", "kilometers")) {
  r <- switch(match.arg(units), miles = R_E_MI, kilometers = R_E_KM)

  x <- XML::xmlInternalTreeParse(file)
  on.exit(XML::free(x))

  dist <- data.frame(dist = unlist(get_trkseg_dist(x, r)))
  dates <- get_dates(x)
  dist$date <- ifelse(length(dates) == nrow(dist), do.call(c, dates), NA)
  dist
}
