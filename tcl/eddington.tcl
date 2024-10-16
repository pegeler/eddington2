#!/usr/bin/env tclsh

proc eddington {file_id} {
  set e 0
  set above 0
  array set h {}
  while {[gets $file_id ride] >= 0} {
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
  if {$argc == 0} {
    return stdin
  } elseif {$argc == 1} {
    return [open [lindex $argv 0] r]
  } else {
    puts stderr "Must provide a file or stdin"
    exit 1
  }
}

proc main {} {
  set file_id [get_file]
  puts [eddington $file_id]
  if {$file_id ne "stdin"} {
    close $file_id
  }
}

main
