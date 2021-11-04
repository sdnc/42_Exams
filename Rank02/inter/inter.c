#include <unistd.h>

void	putchar(char c)
{
	write(1, &c, 1);
}

int	find_dup(char *s, size_t idx)
{
	size_t	i = 0;

	while (i < idx)
	{
		if (s[i] == s[idx])
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	size_t	i;
	size_t	j;
	
	i = 0;	
	if (ac == 3)
	{
		while (av[1][i])
		{
			if (!find_dup(av[1], i))
			{
				j = 0;
				while (av[2][j])
				{
					if (av[1][i] == av[2][j])
					{
						putchar(av[1][i]);
						break ;
					}
					j++;
				}	
			}
			i++;
		}
	}
	putchar('\n');
	return (0);
}
