#include <stdio.h>
int main() {
    int a = 10;
    int* p;
    p = &a;
    printf("a의 값 : %d\n", a);
    printf("a의 주소 : %p\n", &a);
    printf("p에 저장된 값(주소): %p\n", p);
    printf("p가 가리키는 값: %d\n", *p);
    printf("============\n");
    *p = 20;
    printf("a의 값: %d\n", a);
    printf("a의 주소: %p\n", &a);
    printf("p에 저장된 값주소): %p\n", p);
    printf("p가 가리키는 값: &d\n", *p);
    return 0;
}