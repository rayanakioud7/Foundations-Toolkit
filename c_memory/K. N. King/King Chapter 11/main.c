#include <stdio.h>

#define N 10


void decompose(double x, long *int_part, double *frac_part){
        *int_part = (long) x;
        *frac_part = x - *int_part;
    }

void min_max(int a[], int n, int *max, int *min){
    int i;
    *max = *min = a[0];
    for(i =1; i<n ;i++){
        if (a[i] > *max){ *max = a[i];}
        else if (a[i] < *min){ *min = a[i]; }
    }
}

void swap (int *p, int *q){
    int temp = *p;
    *p =*q;
    *q = temp;
}

int main(){
    int i, *p;
    i = 5;
    p = &i;
    printf("*p: %d\n",*p);
    printf("i: %d\n", i);
    *p = 2;
    printf("*p: %d\n",*p);
    printf("p: %p", p);
    printf("i: %d\n", i);

    int *q;
    q = p;
    printf("*q: %d\n", *q);

    *q = 3;
    printf("*p: %d\n",*p);
    printf("i: %d\n", i);
    printf("*q: %d\n", *q);
    int j= 4;
    q =&j;
    printf("*p: %d\n",*p);
    printf("i: %d\n", i);
    printf("*q: %d\n", *q);
    printf("j: %d\n", j);
    
    *p = *q;
    printf("i: %d\n", i);

    long v =14;
    double z = 34.6;
    printf("with pointers i can change the value without caring about the scope of variables\n");
    decompose(3.14159, &v, &z);
    printf("v: %ld\n", v);
    printf("z: %f\n", z);

    printf("*********************\n");
    printf("using pointers with arrays to return 2 values since we cant do That in C but with pointers changing the value of an address in memory is easy even if the function returns void\n");
    int big, small;
    int b[N] = {1,5,3,8,5,9,3,6,3, 76};

    min_max(b, N, &big, &small);
    printf("Biggest of b: %d\n", big);
    printf("smallest of b: %d\n", small);

    int k = 10, Q = 5;
    swap(&k, &Q);
    printf("k=%d, Q=%d\n",k, Q);

    return 0;
}