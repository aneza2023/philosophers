
#include "philosophers.h"

int philosophers(void)
{

}

int main(int argc, char *argv[])
{
    int i;

    i = 1;
    if (argc <= 4 || argc >= 7)
    {
        write (1, "Error\n", 6);
        return (1);
    }
    while (i <= argc - 1)
    {
        if (check_for_input(argv[i], i) == 1)
        {
            write (1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    //philosophers();
    return (0);
}
