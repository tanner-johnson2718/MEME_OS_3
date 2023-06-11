#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int in)
{
    printf("Sig\n");
    return;
}

int main()
{
    printf("b4 signal()\n");
    signal(SIGALRM, sig_handler);

    printf("b4 alarm()\n");
    alarm(1);
    pause();
}