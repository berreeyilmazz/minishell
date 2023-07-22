#include <stdio.h>
#include <signal.h>

void    handler(int signal)
{
    printf("ctrl+c sinyali (SIGINT) alındı.\n");
}

/*int main()
{
    int i = 0;
    signal(SIGINT, handler);
    while(1)
    {
        i++;
        if(!signal(SIGINT, handler))
            return (0);
    }
    return (0);
}


int main(int ac, char **av, char **env) {
	for (char **e = env; *e; e++)
		printf("%s\n", *e);
}*/
