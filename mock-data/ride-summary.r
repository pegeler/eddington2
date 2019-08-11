library(eddington)
library(ggplot2)
library(knitr)
library(papeR)

# Loading in the data --------------------------------------------------------
x <- as.numeric(readLines("rides.dat"))

rides <- data.frame(
  ride_number = seq_along(x),
  ride_length = x,
  E_cumulative = E_cum(x)
)


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
abline(v = 25, col = "darkred")
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
       x = ride_number,
       type = "h",
       main = "Ride Lengths over Time",
       xlab = "Ride Number",
       ylab = "Ride Length (mi)",
       bty = "n"
     )
)


lines(
 y = c(0, rides$E_cumulative),
 x = c(0, rides$ride_number),
 type = "l",
 col = "darkred"
)

legend(
  "topleft",
  legend = "Eddington Number",
  col = "darkred",
  bty = "n",
  lty = 1L
)

dev.off()
