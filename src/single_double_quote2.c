/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:15:13 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 11:19:07 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 1;
	while (arg[++x])
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
	}
	return (nb);
}

int	ft_find_start(char *str, int x)
{
	int	start;

	start = x;
	while (str[x])
	{
		if (str[x] == 124)
		{
			start = x;
			return (start + 1);
		}
		if (str[x] != 124 && str[x] != 32 && str[x] != 9)
		{
			start = x;
			return (start);
		}
		x++;
	}
	return (0);
}

char	**resplit_tab(char **tab)
{
	char	**new;
	int		i;
	int		n;
	int		size;

	i = -1;
	size = 1;
	n = 0;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "|", 1) == 0)
			size++;
	}
	new = ft_calloc((size + 1), sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	i = -1;
	size = 0;
	while (tab[++i])
	{
		if (tab[i + 1] == NULL || ft_strncmp(tab[i + 1], "|", 1) == 0)
		{
			if (n > 0)
				size--;
			new[n] = copy_line(tab, i, size);
			n++;
			size = -1;
		}
		size++;
	}
	new[n] = NULL;
	power_free(tab);
	return (new);
}

char	**ft_split_str(t_shell *shell, char *str, char **tab)
{
	int		z;

	z = -1;
	(void)shell;
	tab = ft_split(str, ' ');
	while (tab[++z])
	{
		if (ft_need_expand(tab[z]) != -1
			&& expand_not_quoted(tab[z], ft_need_expand(tab[z]) == 1))
			tab[z] = ft_ryoiki_tenkai(shell, tab[z],
					ft_need_expand(tab[z]) + 1);
	}
	tab = resplit_tab(tab);
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
