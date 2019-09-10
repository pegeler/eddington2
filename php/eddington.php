#!/usr/bin/env php
<?php
function eddington($rides) {
  
  $n = count($rides);
  
  if (!$n) return 0;

  rsort($rides);
  
  $E = 0;
  for (; $E < $n; $E++) {
    if ($rides[$E] < $E + 1) break;
  }

  return $E;
}

if ($argc > 1) {

  $lines = file($argv[1]);
  foreach ($lines as $line) {
    $rides[] = (float) $line;
  }

  echo eddington($rides)."\n";

}

exit;

?>

