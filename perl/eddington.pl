#!/usr/bin/perl

use warnings;
use strict;

use feature qw(say);

sub get_eddington_number {
  my $eddington_number = 0;
  my $n_above = 0;
  my %dist_table;

  foreach my $dist (<>) {
    $dist = int($dist);
    if ($dist > $eddington_number) {
      $n_above++;
      $dist_table{$dist}++;

      if ($n_above > $eddington_number) {
        $eddington_number++;
        $n_above -= $dist_table{$dist};
        delete $dist_table{$dist};
      }
    }
  }
  say $eddington_number;
}

get_eddington_number;
