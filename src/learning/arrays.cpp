#include <iostream>

void print_array(int* a, int l)
{
  int* p = &a[0];
  for(;p != &a[l-1] ; ++p)
    std::cout << *p;

  std::cout << "\n";
}

void copy_array(int* a, int l)
{
  int n[l];

  int* d = n;
  int* e = n + l;

  while(d != e)
    *d++ = *a++;

  print_array(n, l);
}

int partition(int* a, int p, int q)
{
  int x = a[p];
  int i = p;

  for(int j = p+1; j < q; ++j) {
    if(a[j] <= x) {
      ++i;
      std::swap(a[i], a[j]);
   }
  }

  std::swap(a[p], a[i]);
  return i;
}

void sort(int* a, int p, int q)
{
  int r;

  if(p < q) {
    r = partition(a, p, q);
    sort(a, p, r);
    sort(a, r+1, q);
  }
}

int main(int argc, char** argv)
{
  int array[10] = {0,1,2,3,4,5,6,7,8,9};

  print_array(array, 10);
  copy_array(array, 10);

  std::cout << "Array length: " << (sizeof(array)/sizeof(*array)) << "\n";

  int sarray[10] = {1,5,8,2,3,4,7,9,0,6};
  sort(sarray, 0, 9);
  print_array(sarray, 10);

  return 0;
}
