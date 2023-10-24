/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:59:29 by jquil             #+#    #+#             */
/*   Updated: 2023/10/24 14:28:44 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote_2(char *str, int nb, int type)
{
	int		x;
	int		y;
	char	*new;

	x = -1;
	y = -1;
	new = malloc ((ft_strlen(str) - nb + 1) * sizeof (char));
	if (!new)
		return (NULL);
	x = -1;
	while (str[++x])
	{
		if (str[x] != type && str[x] != 92)
			new[++y] = str[x];
	}
	++y;
	new[y] = '\0';
	return (new);
}

char	*remove_quote(char *str)
{
	int		x;
	int		nb;
	char	*new;
	int		type;

	nb = 0;
	x = -1;
	while (str[++x])
	{
		if (str[x] == 39 || str[x] == 34 || str[x] == 92)
		{
			++nb;
			type = str[x];
		}
	}
	if (nb != 0)
	{
		new = remove_quote_2(str, nb, type);
		free(str);
		return (new);
	}
	else
		return (str);
}

int	count_word_2(char *arg, int x, int nb)
{
	if (arg[x] == 34)
	{
		while (arg[++x] != 34)
			;
	}
	if (arg[x] == 39)
	{
		while (arg[++x] != 39)
			;
	}
	if (arg[x] == 124)
		nb++;
	if (arg[x] != 124 && arg[x] != 9 && arg[x] != 32)
	{
		while (arg[x] && (arg[x] != 124 && arg[x] != 9 && arg[x] != 32))
			x++;
		if (!arg[x])
			return (nb);
	}
	return (nb);
}

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 1;
	while (arg[++x])
	{
		count_word_2(arg, x, nb);
	}
	return (nb);
}
