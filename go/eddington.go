package main

import (
  "bufio"
  "fmt"
  "os"
  "strconv"
)


func get_eddington_number(rides []int) int {
  h := make(map[int]int)
  e, above := 0, 0
  for _, ride := range rides {
    if ride > e {
      above++
      h[ride]++
    }
    if above > e {
      e++
      above -= h[e]
      delete(h, e)
    }
  }
  return e
}

func get_rides() []int {
  var rides []int
  scanner := bufio.NewScanner(os.Stdin)
  for scanner.Scan() {
    ride, _ := strconv.ParseFloat(scanner.Text(), 64)
    rides = append(rides, int(ride))
  }
  return rides
}

func main() {
  rides := get_rides()
  e := get_eddington_number(rides)
  fmt.Println(e)
}
