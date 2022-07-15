#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
const int base = 1000000000;
typedef struct {
    uint32_t size[35];

} uint1024_t;

uint1024_t from_uint(unsigned x) {
    uint1024_t value;
    int i = 0;
    for (i; i<35; i++) {
        value.size[i] = x % base;
        x = x / base;
    }
    return value;
}
void scanf_value(uint1024_t *x) {
    char string[310];
    int i,j =  0;
    for (i; i < 310; i++) {
        string[i] = '\0';
    }
    i = i - 1;
    scanf("%s", string);

    while(string[i] == '\0' ) {
        i = i -1;
    }
    for (int zero = 0;zero <= 34; ++zero) {
        x->size[zero] = 0;
    }
    while (i >= 0) {
        x->size[j / 9] += (string[i]-'0') * pow(10, j % 9);
        ++j;
        --i;
    }
}

void printf_value(uint1024_t x) {
    int i = 34;
    int count = 0;
    while (x.size[i]==0) {
        i--;
    }
    printf("%d",x.size[i]);
    i--;
    while (i>=0) {
    printf("%09d",x.size[i]);
    i--;
    }
}
uint1024_t add_op(uint1024_t x, uint1024_t y) {
uint64_t res;
int dis = 0;
int i = 0;
for (i; i<35; i++) {
    res = x.size[i] + y.size[i] + dis;
    x.size[i] = res % base;
    dis = res / base;

}
return x;
}
uint1024_t subtr_op(uint1024_t x, uint1024_t y) {
uint64_t res;
int dis = 0;
int i = 0;
for (i;i < 35; i ++) {
    res = (x.size[i] + base) - (dis + y.size[i]);
    x.size[i] = (res % base);
    dis = (res >= base) ? 0:1;
}
return (x);
}
uint1024_t mult_op(uint1024_t x, uint1024_t y) {
uint1024_t multip = from_uint(0);
uint64_t res;
uint64_t dis = 0;
int i = 0;
int j = 0;
for (int i=0; i < 35; ++i) {
    for(j=0; (i+j) <35; ++j) {
        res = multip.size[i+j] + ((uint64_t) x.size[i]) * ((uint64_t)y.size[j]) + dis;
        multip.size[i+j] = (res % base);
        dis = res / base;
    }
}
return multip;
}




int main() {
    uint1024_t a;
    uint1024_t b;
    uint1024_t c;
    scanf_value(&a);
    scanf_value(&b);
    printf_value(mult_op(a,b));
    return 0;

}