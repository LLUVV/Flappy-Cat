#include<stdio.h>
typedef struct d_NODE
{
    int a;
    int *ptr;
} NODE;
int main(void)
{
    int b=10;
    NODE point;
    //point=(NODE *)malloc(sizeof(NODE));
    point.ptr=&b;
    printf("%d %d",b,*(point.ptr));
}
