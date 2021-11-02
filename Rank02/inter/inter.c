#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

int	checkdoubles(char *s, char c, int idx)
{
	int	i;
	
	i = 0;
	while (i < idx)
	{
		if (s[i] == c)
			return (1); // yes, there is a double
		i++;
	}
	return (0) // no, there are no previous occurences
}

int	checkmatch(char *str, char c, int index)
{

}

char	*chars_in_common(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
}

int	main(int ac, char **av)
{
	char	*str;

	if (ac == 3)
	{
		str = chars_in_common(av[1], av[2]);
		ft_putstr(str);	
	}
	ft_putchar('\n');
	return (0);
}
