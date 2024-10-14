proc eddington {} {
  set e 0
  set above 0
  array set h {}
  while {[gets stdin ride] >= 0} {
    set ride [expr {int($ride)}]
    if {$ride > $e} {
      incr above
      incr h($ride)
    }
    if {$above > $e} {
      incr e
      if {[info exists h($ride)]} {
        incr above -$h($ride)
        unset h($ride)
      }
    }
  }
  puts $e
}

eddington
