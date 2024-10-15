#!/usr/bin/env tclsh

proc eddington {file} {
  set e 0
  set above 0
  array set h {}
  while {[gets $file ride] >= 0} {
    set ride [expr {int($ride)}]
    if {$ride > $e} {
      incr above
      incr h($ride)
    }
    if {$above > $e} {
      incr e
      if {[info exists h($e)]} {
        incr above -$h($e)
        unset h($e)
      }
    }
  }
  return $e
}

proc get_file {} {
  global argc argv
  if {$argc == 1} {
    # TODO: close file!
    return [open [lindex $argv 0] r]
  } elseif {$argc == 0} {
    return stdin
  } else {
    puts stderr "Must provide a file or stdin"
    exit 1
  }
}

puts [eddington [get_file]]
