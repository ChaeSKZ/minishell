/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 11:18:21 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_not_quoted(char *str, int end)
{
	int	x;
	int	p1;
	int	p2;

	x = -1;
	while (str[++x])
	{
		if (str[x] == 39)
		{
			p1 = x;
			while (str[++x] != 39)
				;
			p2 = x;
			if (end > p1 && end < p2)
				return (0);
		}
		if (str[x] == 34)
		{
			p1 = x;
			while (str[++x] != 34)
				;
			p2 = x;
			if (end > p1 && end < p2)
				return (0);
		}
	}
	return (1);
}

int	expand_not_quoted(char *str, int dollar)
{
	int	x;
	int	p1;
	int	p2;

	x = -1;
	while (str[++x])
	{
		if (str[x] == 39)
		{
			p1 = x;
			while (str[++x] != 39)
				;
			p2 = x;
			if (dollar > p1 && dollar < p2)
				return (0);
		}
	}
	return (1);
}

int	ft_find_end(char *str, int start)
{
	int	end;

	end = start + 1;
	while (str[end])
	{
		if (str[end] == 124 && pipe_not_quoted(str, end) == 1)
			return (end);
		end++;
	}
	return (end);
}

char	**ft_split_quote(t_shell *shell, char *arg)
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
		else if ((arg[x] == 34 && ft_next_quote(arg, 34, x) == 0)
			|| (arg[x] == 39 && ft_next_quote(arg, 39, x) == 0))
			return (NULL);
	}
	return (ft_split_str(shell, arg, tab));
}
