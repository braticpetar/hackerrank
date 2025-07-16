#include <stdio.h>

int absolute_value(int a, int b)
{
    if (a > b) return a-b;
    else if (b > a) return b-a;
    else return 0;
}

void update(int *a,int *b) {
    // Complete this function    
    int sum = *a + *b;
    int diff = absolute_value(*a, *b);
    
    *a = sum;
    *b = diff;
    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
