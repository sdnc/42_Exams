#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	{
	va_list	arg;
	int	count;
}			t_hold;

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}


void	ft_putstr(t_hold *arguments)
{
	char *str;
	int	i;

	str = va_arg(arguments->arg, char *);
	i = 0;
	while (str[i])
		ft_putchar_fd(str[i++], 1);
}

void	ft_itoa(int nb, int len)
{
	int	n;
	int	i = 0;
	char	*str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return ;
	if (nb < 0)
	{
		str[0] = '-';
		n = -nb;
	}
	else
		n = nb;
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	while (str[i])
		ft_putchar_fd(str[i++], 1);
}

void	ft_putnbr(t_hold *arguments)
{
	int	len = 1;
	int	nb_to_convert;
	int	temp;
	
	nb_to_convert = va_arg(arguments->arg, int);
	temp = nb_to_convert;
	if (temp < 0)
	{
		temp = -temp;
		len++;
	}
	while (temp > 9)
	{
		temp /= 10;
		len++;
	}
	ft_itoa(nb_to_convert, len);
	arguments->count += len;	
}

void	ft_puthex(t_hold *arguments)
{
	int	i = 0;
}

void	convert_type(char c, t_hold *arguments)
{
	if (c == 's')
		ft_putstr(arguments);
	else if (c == 'd')
		ft_putnbr(arguments);
	else if (c == 'x')
		ft_puthex(arguments);
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		arguments->count++;
	}
}


static t_hold	*init_args(void)
{
	t_hold	*arguments;

	arguments = (t_hold *)malloc(sizeof(t_hold));
	if (!arguments)
		return (0);
	arguments->count = 0;
	return (arguments);
}

int	ft_printf(char	*str, ...)
{
	t_hold	*arguments;
	int	count;
	int	i;

	i = 0;
	count = 0;
	arguments = init_args();
	va_start(arguments->arg, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			count++;
		}
		else if (str[i] == '%')
			convert_type(str[++i], arguments);
		i++;	
	}
	count += arguments->count;
	va_end(arguments->arg);
	free(arguments);
	return (count);
}

int	main(void)
{	
	char	*name = "Sara";
	int	year = 2022;
	ft_printf("Hey there %s, it's almost %d", name, year);
}
