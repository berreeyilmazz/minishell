void    deneme(int *a)
{
    *a = 5;
}


#include <stdio.h>
int main()
{
    int *p;
    p = 0;

    deneme(p);
    printf("%d\n", *p);
}