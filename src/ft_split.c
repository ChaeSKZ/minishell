/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:51:47 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 17:10:25 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	line(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static char	**split_it(char const *s, char c, char **tab, int size)
{
	int	i;
	int	t;
	int	l;

	i = 0;
	t = 0;
	while (s[i] && t < size)
	{
		l = 0;
		while (s[i] == c)
			i++;
		tab[t] = malloc(sizeof(char) * (line(s, c, i) + 1));
		if (tab[t] == NULL)
			return (power_free(tab), NULL);
		while (s[i] != c && s[i])
			tab[t][l++] = s[i++];
		tab[t][l] = '\0';
		t++;
	}
	tab[t] = NULL;
	return (tab);
}

static int	a_tab(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i++;
			j++;
		}
		s++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		size;

	if (s == NULL)
		return (NULL);
	size = a_tab(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	return (split_it(s, c, tab, size));
}
