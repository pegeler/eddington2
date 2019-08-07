#include <stdio.h>
#include <stdlib.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}

int eddington(int a[], int n)
{
  qsort (a, n, sizeof(int), compare);
  int E = 0;
  for (; E < n; E++) {
    if (a[E] < E + 1) break;
  }

  return E;
}
 
int main(int argc, char *argv[])
{
    int n = argc - 1;
    int a[n];
    
        
    for (int i=0; i<n; i++) 
    {
        sscanf(argv[i + 1], "%i", &a[i]);;
    }
    
    printf("Your Eddington number is: % 3i\n", eddington(a, n));
    
    return 0;
}
