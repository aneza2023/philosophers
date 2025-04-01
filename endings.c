#include "philosophers.h"

int error_input(void)
{
    write(1, "Error'n", 6);
    return (1);
}