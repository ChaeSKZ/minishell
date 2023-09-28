/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/28 17:55:37 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_2(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 0;
	while (arg[++x])
	{
		if (arg[x] != 32 && arg[x] != 9)
		{
			nb++;
			while (arg[x] && arg[x] != 32 && arg[x] != 9)
				x++;
		}
		while (arg[x] && (arg[x] == 32 || arg[x] == 9))
			x++;
	}
	return (nb);
}

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 0;
	while (arg[++x])
	{
		if (arg[x] == 34)
		{
			++x;
			while (arg[x] != 34)
				x++;
			nb++;
		}
		else if (arg[x] == 39)
		{
			++x;
			while (arg[x] != 39)
				x++;
			nb++;
			x++;
		}
	}
	if (nb == 0 && arg != NULL)
		nb = count_word_2(arg);
	return (nb);
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

char	**ft_stock_str(char *arg, int x, int flag, int type)
{
	int		y;
	int		z;
	char	**tab;
	int		target;
	int		tmp;
	y = 0;
	z = 0;
	tmp = flag;
	target = count_word(arg);
	tab = malloc(target * sizeof (char *));
	if (type == 0)
		x = 0;
	while (z < target)
	{
		tab[z] = malloc (((x - flag) + 1) * sizeof(char));
		while (flag < x)
		{
			tab[z][y] = arg[flag];
			y++;
			flag++;
		}
		tab[z][y] = '\0';
		y = 0;
		z++;
		flag = tmp;
	}
	return (tab);
}

char	**ft_split_quote(char *arg)
{
	int		x;
	int		flag;
	int		type;
	char	**tab;

	x = -1;
	flag = 0;
	type = 0;
	while (arg[++x])
	{
		if (arg[x] == 39 && ft_next_quote(arg, 39, x) == 1)
		{
			type = 39;
			flag = x + 1;
			while (arg[++x] && arg[x] != 39)
				;
		}
		else if (arg[x] == 34 && ft_next_quote(arg, 34, x) == 1)
		{
			type = 34;
			flag = x + 1;
			while (arg[++x] && arg[x] != 34)
				;
		}
		else if ((arg[x] == 34 && ft_next_quote(arg, 34, x) == 0) || (arg[x] == 39 && ft_next_quote(arg, 39, x) == 0))
			return (NULL);
		tab = ft_stock_str(arg, x, flag, type);
		flag = x;
	}
	return (tab);
}
