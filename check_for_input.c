
int ft_atoi(char *argv)
{
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;
    while ((str[i] == 32) || (str[i] > 8 && str[i] < 14))
        i++;
    if (str[i] == '-')
    {
        sign = sign * ( - 1);
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] > 47 && str[i] < 58)
    {
        result = result * 10 + str[i] - '0';
        i++;
    }
    result = result * sign;
    return (result);
}

int check_for_input(char *argv)
{
    int nb;
    int i;

    nb = ft_atoi(argv);
    if (nb <=0 || nb > 200)
        return (1);
    while (argv[i] != '\0')
    {
        if (argv[i] < '0' || argv[i] > '9')
            return (1);
        i++;
    }
    return (0);
}