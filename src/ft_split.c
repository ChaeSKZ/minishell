/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:51:47 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/06 16:59:46 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**spower_free(char **tab, int line)
{
	while (line > 0)
	{
		line--;
		free(tab[line]);
	}
	free(tab);
	return (NULL);
}

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
			return (spower_free(tab, t));
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
	split_it(s, c, tab, size);
	return (tab);
}
// var split -> arg & meta
