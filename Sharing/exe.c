#include "lib.h"

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        return is_odd(argv[1]);
    }
    
    return -1;
}