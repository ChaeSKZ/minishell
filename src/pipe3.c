/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:08:05 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 11:34:04 by jugingas         ###   ########.fr       */
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
	new = ft_calloc((tab_len(tab) + 1), sizeof(char *));
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
			new[n] = ft_strcpy(tab[i], new[n]);
			new[++n] = NULL;
			i++;
		}
	}
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

	i = -1;
	if (pp->pid)
	{
		i = -1;
		while (++i < pp->cmd_nb - 1 && pp->pidtab[i] != 0)
			;
		pp->pidtab[i] = pp->pid;
	}
	power_free(no_redirec);
	power_free(tab);
	free(cmd_name);
}
