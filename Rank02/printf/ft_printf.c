#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  {
    va_list args;
    int     counter;
}                   t_hold;

void    ft_putchar(char c) 
{
    write(1, &c, 1);
}

void    put_string(t_hold *arguments)
{
    char    *s;

    s = va_arg(arguments->args, char *);
    while (*s)
    {
        write(1, s++, 1);
		arguments->counter++;
		//printf("	count += %d\n", 1);
    }    
}

void    ft_itoa(int nb, int len)
{
    char    *str;
	int 	i = 0;

    str = (char *)malloc(sizeof(char) * len + 1);
    if (!str)
        return ;
    if (nb < 0)
    {
        str[0] = '-';
        nb = -nb;
    }
    if (nb == 0)
        str[0] = '0';
    str[len--] = '\0';
    while (nb)
    {
        str[len--] = nb % 10 + '0';
        nb /= 10;
    }
    while (str[i])
        ft_putchar(str[i++]);
    free(str);
}

void    long_to_hex(unsigned int nb, int len)
{
    char    *str;
    int     i = 0;

    str = (char *)malloc(sizeof(char) * len + 1);
    if (!str)
        return ;
    str[len--] = '\0';
    while (len >= 0)
    {
        if (nb % 16 < 10)
        {
            str[len] = nb % 16 + '0';
        }
        else
        {
            str[len] = 'a' - 10 + (nb % 16);
        }
        len--;
        nb /= 16;
    }
    while (str[i])
        ft_putchar(str[i++]);
    free(str);
}

void    put_int(t_hold *arguments)
{
    int nb;
    int len = 1;
    int temp;

    nb = va_arg(arguments->args, int);
    temp = nb;
    if (temp < 0)
    {
        len++;
        temp = -nb;
    }
    while (temp > 9)
    {
        len++;
        temp /= 10;
    }
    ft_itoa(nb, len);
	//printf("	count += %d\n", len);
    arguments->counter += len;
}

void    put_hex(t_hold *arguments)
{
    unsigned int    address_nb;
    int             len = 1;
    unsigned int    temp;

    address_nb = va_arg(arguments->args, unsigned long);
    temp = address_nb;
    while (temp > 16)
    {
        len++;
        temp /= 16;
    }
    long_to_hex(address_nb, len);
	printf("	count += %d\n", len);
    arguments->counter += len;
}

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
        arguments->counter += 1;
		//printf("	count += %d\n", 1);
    }
}

static t_hold   *init_args()
{
    t_hold *arguments;

    arguments = (t_hold *)malloc(sizeof(t_hold));
    if (!arguments)
        return (NULL);
    arguments->counter = 0;
    return (arguments);
}

int ft_printf(char *str, ...)
{
    t_hold  *arguments;
    int     i = 0;
    int     count = 0;

    arguments = init_args();
    va_start(arguments->args, str);
    while (str[i])
    {
        if (str[i] != '%')
        {
            ft_putchar(str[i]);
            count++;
			//printf("	count += %d\n", 1);
        }
        else 
            convert_type(str[++i], arguments);
        i++;
    }
    count += arguments->counter;
    va_end(arguments->args);
    free(arguments);
	//printf("\nA total count of: %d characters\n", count);
    return (count);
}

int main(void)
{
    char    *name = "Sara";
    int     year = -2021;
    int     *place = &year;

    ft_printf("Hello there %s. 90%% of %d is over. Meet me at %x", name, year, place);
    return (0);
}