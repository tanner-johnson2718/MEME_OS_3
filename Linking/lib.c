#define STRING "Hello"

static char* string_ptr = STRING;
int lib_gbl = 9;

char* get_str() {
    return string_ptr;
}