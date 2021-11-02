#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	*ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
			i++;
	while (src[j])
		dest[i++] = src[j++];
	src[j] = '\0';
	return (dest);
}

char	*checkdup(char *str)
{
	size_t	i;
	size_t	j;
	int		dup;

	i = 0;
	dup = 0;
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
		checkdup(str);
	if (dup == 0)
		str[i] = '\0';
	return (str);
}

int	main(int ac, char **av)
{
	char	*str;

	if (ac == 3)
	{
		str = ft_strcat(av[1], av[2]);
		ft_putstr("Merging the strings together: ");
		ft_putstr(str);
		ft_putchar('\n');
		str = checkdup(str);
		ft_putstr("Removing doubles: ");
		ft_putstr(str);	
	}
		ft_putchar('\n');
		return (0);
}
