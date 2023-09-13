/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/12 16:32:59 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		x;
	int		y;
	char	*argtmp;

	x = 0;
	y = 0;
	shell->meta[0] = ft_single_or_double(arg);
	argtmp = malloc ((ft_strlen(arg)) * sizeof(char));
	if (shell->meta == 0)
		return (free(argtmp), arg);
	else
	{
		while (x < ft_strlen(arg))
		{
			if ((shell->meta[0] == 1 && arg[x] != 39)
				|| (shell->meta[0] == 2 && arg[x] != 34))
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
	if (ft_single_or_double(arg) != 0)
		arg = ft_split_quote(shell, arg);
	return (arg);
}
