/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:15:13 by jquil             #+#    #+#             */
/*   Updated: 2023/10/19 15:17:19 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**resplit_tab_2(char **tab, char **new, int i, int size)
{
	int	n;

	n = 0;
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
	if (tab)
		power_free(tab);
	return (new);
}

char	**resplit_tab(char **tab)
{
	char	**new;
	int		i;
	int		size;

	i = -1;
	size = 1;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "|", 1) == 0)
			size++;
	}
	new = ft_calloc((size + 1), sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	new = resplit_tab_2(tab, new, i, size);
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
		if (ft_need_expand(tab[z]) != -1 && expand_not_quoted(tab[z], ft_need_expand(tab[z])) == 1)
		{
			tab[z] = ft_extension_of_the_territory(shell, tab[z],
					ft_need_expand(tab[z]) + 1);
		}
		else
			tab[z] = remove_quote(tab[z]);
	}
	tab[z] = NULL;
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
