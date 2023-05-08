#include <stdio.h>

char* get_str();

int main(int argc, char** argv) {
    char* s = get_str();
    printf("Returned String = %s\n", s);
    return 0;
}