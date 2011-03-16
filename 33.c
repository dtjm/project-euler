#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int num;
  int den;
} frac_t;

void frac_print(frac_t frac)
{
  printf("%d/%d", frac.num, frac.den);
}

frac_t frac_cancel(frac_t frac)
{
  char num_tens, num_ones, den_tens, den_ones;
  num_tens = frac.num / 10;
  num_ones = frac.num - (num_tens * 10);
  den_tens = frac.den / 10;
  den_ones = frac.den - (den_tens * 10);
  frac_t cancelled_frac;
  if(num_ones == den_tens) 
  {
    cancelled_frac.num = num_tens;
    cancelled_frac.den = den_ones;
    return cancelled_frac;
  }
  else 
    return frac;
}

frac_t frac_mult(frac_t f1, frac_t f2)
{
  frac_t prod;
  prod.num = f1.num * f2.num;
  prod.den = f1.den * f2.den;
  return prod;
}

float frac_to_dec(frac_t f)
{
  return (float) f.num / f.den;
}

bool frac_equals(frac_t f1, frac_t f2)
{
  return frac_to_dec(f1) == frac_to_dec(f2);
}

int main(int argc, char **argv)
{
  // Loop through all eligible fractions
  int i,j,res_index = 0;
  frac_t f1,f2;
  frac_t results[4];

  for(i = 10; i < 100; i++)
  {
    f1.num = i;
    for(j = 10; j < 100; j++) 
    {
      if(0 == i % 10 && 0 == j % 10) 
        break;
      else if(0 == i % 11 && 0 == j % 11)
        break;

      f1.den = j;
      f2 = frac_cancel(f1);

      if(frac_equals(f1, f2) && f1.num != f2.num)
      {
        results[res_index++] = f2;
      }
    }
  }

  f1.num = f1.den = 1;
  for(i = 0; i < 4; i++)
  {
    f1 = frac_mult(f1, results[i]);
  frac_print(f1);
  puts("");
  }


  return 0;
}
