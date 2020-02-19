#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char	*rev_a(char *str)
{
	int	k;
	char	*out;
	float	flo;
	char	*end;
	char	*new;
	int	j;

	k = 0;
	while (str[k] && str[k] != 'A')
		k++;
	if (str[k] == 'A')
	{
		flo = 3.1415926535 - atof(str + k + 1);
		j = 1;
		while (ft_isdigit(str[k + j]))
			j++;
		if (str[k + j] == '.')
			j++;
		while (ft_isdigit(str[k + j]))
			j++;
		end = ft_strdup(str + k + j);
		str[k + 1] = 0;
		new = (char*)malloc(sizeof(char) * 20);
		ft_memset(new, 0, sizeof(new));
		ftoa(flo, new, 9);
		out = ft_strjoin(str, new);
		free(str);
		str = ft_strjoin(out, end);
		free(out);
		free(end);
		return (str);
	}
	else
	{
		ft_putstr("rrr");
		out = ft_strjoin(str, " A3.14");
		free(str);
		str = out;
		return (str);
	}
}

char	*rev_x(char *str)
{
	char	*rev;
	char	*start;
	int	k;

	k = 0;
	while (str[k] && str[k] != 'X')
		k++;
	if (str[k] == 'X')
	{
		rev = ft_strdup(str + k + 1);
		str[k + 1] = 0;
		start = ft_strjoin(str, "-");
		free(str);
		str = ft_strjoin(start, rev);
		free(start);
		start = NULL;
	}
	return (str);
}


char	*reverse_side(char *str)
{
	str = rev_x(str);
	str = rev_a(str);
	ft_putstr("reversed as: ");
	ft_putstr(str);
	ft_putstr("\n");
	return (str);
}

