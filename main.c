#include <stdio.h>
int main (void){
    printf("%s%s\n", "hello", "world");
    printf("%d\n", 42);
    printf("%c\n",'A');

    char str1[] = "Oregon State Cascades";\
    char str2[]={'O','S','U','C','\0'};

    printf("str1: \t%s\n", str1);
    printf("str2: \t%s\n", str2);

    printf("CHAR[4]:\t%c\n",str1[3]);
    printf("out")
    return 0;
}