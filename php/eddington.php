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
?>
