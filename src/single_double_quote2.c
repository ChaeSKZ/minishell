/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:15:13 by jquil             #+#    #+#             */
/*   Updated: 2023/10/09 14:15:34 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 0;
	while (arg[++x])
	{
		if (arg[x] == 39)
		{
			while (arg[++x] && arg[x] != 39)
				;
			nb++;
		}
		if (arg[x] == 34)
		{
			while (arg[++x] && arg[x] != 34)
				;
			nb++;
		}
		if (arg[x] != 34 && arg[x] != 39 && arg[x] != 9 && arg[x] != 32)
		{
			while (arg[x] && (arg[x] != 34 && arg[x] != 39
					&& arg[x] != 9 && arg[x] != 32))
				x++;
			nb++;
			if (!arg[x])
				return (nb);
		}
	}
	return (nb);
}

int	ft_find_start(char *str, int x)
{
	int	start;

	start = x;
	while (str[x])
	{
		if (str[x] == 34)
		{
			start = x;
			return (start + 1);
		}
		if (str[x] == 39)
		{
			start = x;
			return (start + 1);
		}
		if (str[x] != 39 && str[x] != 34 && str[x] != 32 && str[x] != 9)
		{
			start = x;
			return (start);
		}
		x++;
	}
	return (0);
}
