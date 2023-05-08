#include <stdio.h>

int main(int argc, char** argv) {
    switch(argc) {
        case 1:
            printf("One\n");
            break;
        case 2:
            printf("Two\n");
            break;
        default:
            printf("More\n");
    }
}