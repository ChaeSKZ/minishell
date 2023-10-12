/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:08:05 by jquil             #+#    #+#             */
/*   Updated: 2023/10/12 17:46:34 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ignore_redirections(char **tab)
{
	int		i;
	char	**new;
	int		n;

	i = 0;
	n = 0;
	new = malloc(sizeof(char *) * (tab_len(tab) + 1));
	if (!new)
		return (perror("malloc"), NULL);
	while (tab[i])
	{
		if ((!ft_strncmp(tab[i], ">", 1)
				|| !ft_strncmp(tab[i], ">>", 2)
				|| !ft_strncmp(tab[i], "<", 1)
				|| !ft_strncmp(tab[i], "<<", 2))
			&& tab[i + 1] && tab[i])
			i += 2;
		else
		{
			new[n] = tab[i];
			new[++n] = NULL;
			i++;
		}
	}
	power_free(tab);
	return (new);
}

int	redirect(char **cmdtab, int i)
{
	int		fd;

	fd = 0;
	if (!ft_strncmp(cmdtab[i], ">", 2) && cmdtab[i + 1])
	{
		fd = simple_right(cmdtab[i + 1]);
		dup2(fd, STDOUT_FILENO);
	}
	if (!ft_strncmp(cmdtab[i], ">>", 2) && cmdtab[i + 1])
	{
		fd = double_right(cmdtab[i + 1]);
		dup2(fd, STDOUT_FILENO);
	}
	if (!ft_strncmp(cmdtab[i], "<", 2) && cmdtab[i + 1])
	{
		fd = simple_left(cmdtab[i + 1]);
		dup2(fd, STDIN_FILENO);
	}
	if (!ft_strncmp(cmdtab[i], "<<", 2) && cmdtab[i + 1])
	{
		fd = double_left(cmdtab[i + 1]);
		dup2(fd, STDIN_FILENO);
	}
	return (fd);
}
