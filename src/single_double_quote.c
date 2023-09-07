/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/07 14:07:22 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_single_or_double(char *arg )
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
		}
		else if (arg[x] == 34)
		{
			while (++x < ft_strlen(arg))
				if (arg[x] == 34)
					return (2);
		}
	}
	return (0);
}

char	*ft_split_quote(t_shell *shell, char *arg)
{
	int	x;
	int	nb;
	int	type;

	x = -1;
	nb = 0;
	type = ft_single_or_double(arg);
	if (type == 0)
		return (NULL);
	else if (type == 1)
	{
		while (++x < ft_strlen(arg))
		{
			if (arg[x] == 39)
				++nb;
		}
		if (nb == 2)
			shell->meta[0] = 1;
		x = -1;
		while (++x < ft_strlen(arg))
		{
			if (arg[x] == 39)
			{
				while (x <= ft_strlen(arg))
				{
					arg[x] = arg[x + 1];
					++x;
				}
			}
		}
	}
	else
	{
		x = -1;
		nb = 0;
		while (++x < ft_strlen(arg))
		{
			if (arg[x] == 34)
				++nb;
		}
		if (nb == 2)
			shell->meta[0] = 2;
		x = -1;
		//printf("oui\n");
		while (++x < ft_strlen(arg))
		{
			if (arg[x] == 34)
			{
				while (x <= ft_strlen(arg))
				{
					arg[x] = arg[x + 1];
					++x;
				}
			}
		}
	}
	return (arg);
	// si nb != 2 -> quote = char
}
