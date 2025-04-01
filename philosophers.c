
#include "philosophers.h"

int main(int argc, char *argv[])
{
    int i;

    i = 1;
    if (argc <= 4 || argc >= 7)
    {
        write (1, "Error\n", 6);
        return (1);
    }
    else
    {
        while (i <= 4) // need to do another check if 5th argument >> can as only one be 0
        {
            if (check_for_input(argv[i]) == 1)
            {
                write (1, "Error\n", 6);
                return (1);
            }
            i++;
        }
        //philosophers();
        printf("ddd");
    }
    return (0);
}
