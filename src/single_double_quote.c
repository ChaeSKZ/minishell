/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/05 15:53:00 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	printf("type = %i\n", type);
	if (type == 0)
	{
		printf("oui 1\n");
		return (NULL);
	}
	else if (type == 1)
	{
		printf("oui 2\n");
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
				while (x < ft_strlen(arg))
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
		while (++x < ft_strlen(arg))
		{
			printf("arg : %s\n", arg);
			if (arg[x] == 34)
			{
				while (x < ft_strlen(arg))
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
