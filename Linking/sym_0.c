extern int undef_sym;

int global_init = 1;
int global_uninit;

static int static_global_init =1;
static int static_global_uninit;

int f1()
{
    return 0;
}

int main() {
    int local = 0;
    static int static_local = 1;

    local = undef_sym;
}
