library(eddington)
library(knitr)
library(papeR)

# Loading in the data --------------------------------------------------------
x <- as.numeric(readLines("rides.dat"))

rides <- data.frame(
  ride_day = seq_along(x),
  ride_length = x,
  E = E_cum(x)
)

E <- rides[nrow(rides), "E"]

E_contribs <- rides[rides$ride_length >= E,]

# Summary Statistics ------------------------------------------------------

kable(
  summarize(
    rides,
    variables = c("ride_length", "E_cumulative"),
    labels = c("Ride Length", "Cumulative E")
  )
)

# Histogram ---------------------------------------------------------------

png("hist.png", width = 800, height = 600)

hist(x, breaks = 30, main = "Histogram of Ride Lengths", xlab = "Ride Length (mi)")

abline(v = E, col = "darkred")

legend(
  "topright",
  legend = "Eddington Number",
  col = "darkred",
  bty = "n",
  lty = 1L
)

dev.off()


# Needle plot ------------------------------------------------------------

png("needle.png", width = 800, height = 600)

with(rides,
     plot(
       y = ride_length,
       x = ride_day,
       type = "h",
       main = "Ride Lengths over Time",
       xlab = "Ride Day",
       ylab = "Ride Length (mi)",
       bty = "n",
       ylim = c(0, 90)
     )
)


lines(
  y = c(0, rides$E),
  x = c(0, rides$ride_day),
  type = "l",
  col = "darkred"
)

abline(h = E, lty = 2L, col = "darkred")

text(
  E_contribs[,1:2],
  labels = as.integer(E_contribs[[2]]),
  pos = 3,
  cex = 0.7
  )

legend(
  "topleft",
  title = "Eddington Number",
  legend = c("Cumulative", "Summary"),
  col = "darkred",
  bty = "n",
  lty = c(1L, 2L)
)


dev.off()
