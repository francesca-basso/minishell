#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*y;

	x = 0;
	y = s;
	while (n > 0)
	{
		y[x] = '\0';
		x++;
		n--;
	}
}

void ft_putstr(char *s)
{
    write(1, s, ft_strlen(s));
}