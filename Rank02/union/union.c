#include <unistd.h>

void    ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

char    *ft_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return (dest);
}

char    *find_dup(char *str)
{
    int i = 0;
    int j;
    int dup = 0;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] == str[j])
            {
                str[j] = str[j + 1];
                dup++;
            }
            j++;
        }
        i++;
    }
    if (dup > 0)
        find_dup(str);
    str[i] = '\0';
    return (str);
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        ft_putstr(find_dup(ft_strcat(av[1], av[2])));
    }
    write(1, "\n", 1);
    return (0);
}