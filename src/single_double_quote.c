/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/10/09 16:33:55 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_end(char *str, int start)
{
	int	end;

	end = start + 1;
	while (str[end])
	{
		if (str[start] == 34 || str[start] == 39)
		{
			while (str[end] != str[start])
				end++;
			return (end);
		}
		if (str[start] != 39 && str[start] != 34
			&& str[start] != 32 && str[start] != 9)
		{
			while (str[end] && (str[end] != 39
					&& str[end] != 34 && str[end] != 32 && str[end] != 9))
				end++;
			return (end);
		}
		end++;
	}
	return (end);
}

char	*ft_add_str(char *str, int start, int end)
{
	char	*dest;
	int		x;

	x = 0;
	dest = malloc ((end - start + 1) * sizeof(char));
	while (start < end)
	{
		dest[x] = str[start];
		start++;
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

char	**ft_split_str(char *str, char **tab)
{
	int		target;
	int		x;
	int		start;
	int		end;
	int		z;

	x = -1;
	z = 0;
	target = count_word(str);
	tab = malloc((target + 1) * sizeof (char *));
	while (str[++x] && z < target)
	{
		start = ft_find_start(str, x);
		end = ft_find_end(str, start);
		if (str[end])
			x = end;
		tab[z] = ft_add_str(str, start, end);
		z++;
	}
	tab[z] = NULL;
	return (tab);
}

bool	ft_next_quote(char *arg, int type, int x)
{
	int	y;

	y = x;
	while (arg[++y])
	{
		if (arg[y] == type)
			return (1);
	}
	return (0);
}

char	**ft_split_quote(char *arg)
{
	int		x;
	char	**tab;

	tab = NULL;
	x = -1;
	while (arg[++x])
	{
		if (arg[x] == 39 && ft_next_quote(arg, 39, x) == 1)
		{
			while (arg[++x] && arg[x] != 39)
				;
		}
		else if (arg[x] == 34 && ft_next_quote(arg, 34, x) == 1)
		{
			while (arg[++x] && arg[x] != 34)
				;
		}
		else if ((arg[x] == 34
				&& ft_next_quote(arg, 34, x) == 0)
			|| (arg[x] == 39 && ft_next_quote(arg, 39, x) == 0))
			return (NULL);
	}
	return (ft_split_str(arg, tab));
}
