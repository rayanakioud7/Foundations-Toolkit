#include <stdio.h>

int main(){

    int a[3], *p;
    p = &a[0];

    *p = 5;
    printf("a[0]=%d\n",*p);

    a[2]= 7;
    p+=2;
    printf("a[2]=%d\n",*p);

    a[1] = 3;
    p-=1;
    printf("a[1]=%d\n",*p);

    int *q = &a[0];
    if (p>=q){
        printf("p is after q \n");
    }else {
        printf("p is before q\n");
    }

    int *j;
    for (j = &a[0]; j<&a[3]; j++){
        printf("a[%p]=%d\n", j,*j);
    }

    int *k = &a[0], sum =0;
    while(k < &a[3]){
        sum += *k++;
    } 
    printf("sum=%d\n", sum);



    for (int i=0; i<3; i++){
        *(a+i)=9-i;
        printf("a[%d]=%d\n",i,*(a+i));
    }

    printf("dealing with 2d arrays or multidimension ones is pretty easy with pointers\n since C stores it ina contigueuse way in memory \n you can use a pointer to go though all of that memory line from 0 to a[i-1][j-1]");
/*
    int *p;
    for (p=&a[0][0]; p<= &a[i-1][j-1]; p++){
        *p = 0;
    }
*/

    return 0;

}