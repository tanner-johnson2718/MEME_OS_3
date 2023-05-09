#include <stdio.h>

int exe_gbl = 7;

// lib.c references
char* get_str();
extern int lib_gbl;

int main(int argc, char** argv) {
    puts(get_str());

    int ref1 = exe_gbl;
    int ref2 = lib_gbl;
    int ref3 = exe_gbl;

    return 0;
}