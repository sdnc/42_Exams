#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    va_list args;
    int     count;
}               t_hold;

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    put_string(t_hold *arguments)
{
    char    *str;
    int     i = 0;

    str = va_arg(arguments->args, char *);
    while (str[i])  
    {
        ft_putchar(str[i]);
        arguments->count++;
        i++;
    }  
}

void    long_to_hex(unsigned int nb, int len)
{
        char *str;
        int   i = 0;

        str = (char *)malloc(sizeof(char) * len + 1);
        if (!str)
            return ;
        str[len--] = '\0';
        while (nb)
        {
            if (nb % 16 < 10)
                str[len] = nb % 16 + '0';
            else
                str[len] = 'a' - 10 + (nb % 16);
            len--;
            nb /= 16;
        }
        while (str[i])
            ft_putchar(str[i++]);
}

void    ft_itoa(int nb, int len)
{
    unsigned int    number;
    char            *str;
    int             i = 0;

    str = (char *)malloc(sizeof(char) * len + 1);
    if (!str)
        return ;
    if (nb < 0)
    {
        str[0] = '-';
        number = (unsigned int)-nb;
    }
    else
        number = (unsigned int)nb;
    if (number == 0)
        str[0] = '0';
    str[len--] = '\0';
    while (number)
    {
        str[len--] = number % 10 + '0';
        number /= 10;
    }
    while (str[i])
        ft_putchar(str[i++]);
    free(str);
}

void    put_hex(t_hold *arguments)
{
    unsigned int nb;
    unsigned int temp;
    int          len = 1;

    nb = va_arg(arguments->args, unsigned long);
    temp = nb;
    while (temp > 15)
    {
        len++;
        temp /= 16;
    }
    arguments->count += len;
    long_to_hex(nb, len);
}

void    put_int(t_hold *arguments)
{
    int nb;
    int temp;
    int len = 1;

    nb = va_arg(arguments->args, int);
    temp = nb;
    if (temp < 0)
    {
        len++;
        temp = -temp;
    }
    while (temp > 9)
    {
        len++;
        temp /= 10;
    }
    arguments->count += len;
    ft_itoa(nb, len);

void    convert_type(char c, t_hold *arguments)
{
    if (c == 's')
        put_string(arguments);
    else if (c == 'd')
        put_int(arguments);
    else if (c == 'x')
        put_hex(arguments);
    else if (c == '%')
    {
        ft_putchar('%');
        arguments->count++;
    }
}

static void *init_args(void)
{
    t_hold  *arguments;

    arguments = (t_hold *)malloc(sizeof(t_hold));
    if (!arguments)
        return (NULL);
    arguments->count = 0;
    return (arguments);
}

int ft_printf(char *str, ...)
{
    t_hold *arguments;
    int     i = 0;
    int     counter = 0;

    arguments = init_args();
    va_start(arguments->args, str);
    while (str[i])
    {
        if (str[i] != '%')
        {
            ft_putchar(str[i]);
            counter++;
        }
        else
            convert_type(str[++i], arguments);
        i++;
    }
    counter += arguments->count;
    va_end(arguments->args);
    free(arguments);
    return (counter);
}

int main(void)
{
    char    *name = "Sara";

    ft_printf("Max int: %d, Min int %d, name: %s, max int in hex: %x\n", 2147483647, -2147483647, name, 2147483647);
    return (0);
}