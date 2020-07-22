package io_.github.pegeler.eddington;

import java.util.Scanner;
import java.util.HashMap;

public class Eddington
{
  private int E = 0;
  private int above = 0;
  private HashMap<Integer, Integer> h = new HashMap<Integer, Integer>();

  public int get() { return E; }

  public void update(int r)
  {
    if (r > E) {
      above++;
      h.merge(r, 1, Integer::sum);
      if (above > E)
        above -= h.getOrDefault(++E, 0);
    }
  }

  public void readData(Scanner scan)
  {
    while (scan.hasNext()) {
      update((int) scan.nextFloat());
    }
  }
}

