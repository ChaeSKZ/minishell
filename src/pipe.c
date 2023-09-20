/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/19 18:03:27 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pp *pp, char *cmd, char **env, char **next)
{
	int	i;
	int	fd;

	pp->pid = fork();
	fd = 0;
	if (pp->pid == 0)
	{
		if (pp->idx == 0 && next[0][0] == '<')
		{
			fd = simple_left(next[1]);
			dup2(fd, 0);
			dup2(pp->pipe[1], 1);
		}
		else if (pp->idx < pp->cmd_nb - 1)
			dup2_spe(pp->pipe[2 * pp->idx - 2], pp->pipe[2 * pp->idx + 1]);
		else if (next[0] && next[0][0] == '>' && !next[0][1])
			dup2_spe(pp->pipe[2 * pp->idx - 2], simple_right(next[1]));
		else if (next[0] && next[0][0] == '>' && next[0][1] == '>')
			dup2_spe(pp->pipe[2 * pp->idx - 2], double_right(next[1]));
		else
			dup2_spe(pp->pipe[2 * pp->idx - 2], STDOUT_FILENO);
		close_pipes(pp);
		execve(get_cmd(cmd), ft_split(cmd, ' '), env);
	}
	else
	{
		i = -1;
		while (++i < pp->cmd_nb - 1 && pp->pidtab[i] != 0)
		pp->pidtab[i] = pp->pid;
	}
}

void	init_pidtab(t_pp *pp)
{
	int	i;

	i = -1;
	pp->pidtab = malloc(sizeof(int) * pp->cmd_nb);
	if (!pp->pidtab)
		perror("malloc");
	else
		while (++i < pp->cmd_nb)
			pp->pidtab[i] = 0;
}

void	wait_childs(t_pp *pp)
{
	int	i;

	i = -1;
	while (++i < pp->pipe_nb)
		waitpid(pp->pidtab[i], NULL, 0);
	free(pp->pipe);
	free(pp->pidtab);
}

int	ft_pipe(t_shell *shell, char **token)
{
	t_pp	pp;
	int		i;

	pp.cmd_nb = cmd_count(token);
	if (pp.cmd_nb == 1 && !token[1])
		return (0);
	pp.pipe_nb = 2 * (pp.cmd_nb - 1);
	pp.pipe = malloc(sizeof(int) * pp.pipe_nb);
	init_pidtab(&pp);
	if (!pp.pipe || !pp.pidtab)
		return (perror("malloc"), 0);
	create_pipes(&pp);
	pp.idx = -1;
	i = 0;
	while (++(pp.idx) < pp.cmd_nb)
	{
		child(&pp, token[i], shell->env, token + i + 1);
		if (token[i + 1] && token[i + 1][0] == '<')
			i += 2;
		i += 2;
	}
	close_pipes(&pp);
	wait_childs(&pp);
	return (1);
}
