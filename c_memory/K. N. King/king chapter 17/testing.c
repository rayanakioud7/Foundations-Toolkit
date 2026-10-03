#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2);

int main(){
    char *p;
    p = malloc(sizeof(char)*100);
    if (p == NULL){
        printf("not enough memory space\n");
    }else {
        printf("success\n");
    }
    strcpy(p, "hello everybody\n");
    printf("%s", p);

    free(p);

    
    const char *a = "abc";
    const char *b = "def" ;

    char *s = concat(a,b);
    printf("%s\n", s);
    free(s);
    return 0;

}

char *concat(const char *s1, const char *s2){
    char *result;
    result = malloc(strlen(s1)+strlen(s2)+1);
    if(result == NULL){
        printf("Error: malloc failed in concat\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}