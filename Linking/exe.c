#include <stdio.h>

char* get_str();
int exe_gbl = 7;

int main(int argc, char** argv) {
    puts(get_str());
    return 0;
}