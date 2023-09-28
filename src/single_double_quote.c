/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/28 11:57:44 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = -1;
	while (arg[++x])
	{
		if (arg[x] == 34)
		{
			while (arg[x] != 34)
				x++;
			nb++;
		}
		else if (arg[x] == 39)
		{
			while (arg[x] != 39)
				x++;
			nb++;
		}
		else if (arg[x] == 32)
			nb++;
	}
	return (nb);
}

char	**ft_split_quote(char *arg)
{
	char	**tab;
	int		x;
	int		y;
	int		z;
	int		flag;

	x = 0;
	y = 0;
	z = 0;
	flag = 0;
	tab = malloc(count_word(arg) * sizeof (char *));
	while (arg[z] && x < count_word(arg))
	{
		while (arg[z] == 39 || arg[z] == 34 || arg[z] == 32)
			z++;
		flag = z;
		while (arg[z] != 39 && arg[z] != 34 && arg[z] != 32)
			z++;
		tab[x] = malloc (((z - flag) + 1) * sizeof(char));
		while (flag < z)
		{
			tab[x][y] = arg[flag];
			y++;
			flag++;
		}
		while (arg[z] == 39 || arg[z] == 34 || arg[z] == 32)
			z++;
		tab[x][y] = '\0';
		y = 0;
		x++;
	}
	return (tab);
}
