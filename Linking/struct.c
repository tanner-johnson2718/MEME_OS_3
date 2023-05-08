#include <stdio.h>

struct dat {
    int num;
    char c;
};

int main() {
    struct dat dat1;
    dat1.c = 'c';
    dat1.num = 1;
}