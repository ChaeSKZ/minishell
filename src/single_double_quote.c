/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/27 14:30:08 by jquil            ###   ########.fr       */
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
/*
int	ft_single_or_double(char *arg)
{
	int	x;

	x = -1;
	while (++x < ft_strlen(arg))
	{
		if (arg[x] == 39)
		{
			while (++x < ft_strlen(arg))
				if (arg[x] == 39)
					return (1);
			return (-1);
		}
		else if (arg[x] == 34)
		{
			while (++x < ft_strlen(arg))
				if (arg[x] == 34)
					return (2);
			return (-1);
		}
	}
	return (0);
}

int	count_word(char *arg)
{
	int	x = -1;
	int	nb = 1;

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
char	*ft_split_quote(t_shell *shell, char *arg)
{
	int		x;
	int		y;
	int		*tab;
	char	*argtmp;
	int		comp;

	x = 0;
	y = 0;
	(void)shell;
	tab = malloc (count_word(arg) * sizeof(int));
	comp = ft_single_or_double(arg);
	if (comp == -1)
		return (NULL);
	argtmp = malloc ((ft_strlen(arg)) * sizeof(char));
	if (comp == 1 || comp == 2)
	{
		while (x < ft_strlen(arg))
		{
			if ((comp == 1 && arg[x] != 39) || (comp == 2 && arg[x] != 34))
				argtmp[y++] = arg[x++];
			else
				++x;
		}
	}
	argtmp[x - 2] = '\0';
	x = -1;
	while (argtmp[++x])
		arg[x] = argtmp[x];
	arg[x] = '\0';
	free(argtmp);
	if (comp == 2 || comp == 0)
		;//ft_expend
	return (arg);
}
*/
