/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:08:05 by jquil             #+#    #+#             */
/*   Updated: 2023/10/24 13:08:49 by jugingas         ###   ########.fr       */
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

int	is_redirect(char *str, char *next)
{
	if ((!ft_strncmp(str, ">", 1)
			|| !ft_strncmp(str, ">>", 2)
			|| !ft_strncmp(str, "<", 1)
			|| !ft_strncmp(str, "<<", 2))
		&& next && str)
		return (2);
	return (0);
}

char	**ignore_redirections(char **tab, int fr)
{
	int		i;
	char	**new;
	int		n;

	i = 0;
	n = 0;
	new = ft_calloc((tab_len(tab) + 1), sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	while (tab[i])
	{
		i += is_redirect(tab[i], tab[i + 1]);
		if (tab[i])
		{
			new[n] = ft_strdup(tab[i]);
			new[++n] = NULL;
			i++;
		}
	}
	if (fr)
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

void	end_pipe(t_pp *pp, char **no_redirec, char **tab, char *cmd_name)
{
	int	i;

	(void)cmd_name;
	(void)no_redirec;
	(void)tab;
	i = -1;
	if (pp->pid)
	{
		i = -1;
		while (++i < pp->cmd_nb - 1 && pp->pidtab[i] != 0)
			;
		pp->pidtab[i] = pp->pid;
	}
}
