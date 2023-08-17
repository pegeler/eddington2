package io_.github.pegeler.eddington;

import java.util.Scanner;

public class Main
{
  public static void main(String[] args)
  {
    Eddington e = new Eddington();
    Scanner input = new Scanner(System.in);
    e.readData(input);
    System.out.println(e.get());
  }
}

