/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/07 16:24:27 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(char **token)
{
	int	i;

	i = 0;
	while (token[i] && (i == 0 || token[i - 1]))
		i += 2;
	return (i / 2);
}

void	create_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < pp->cmd_nb - 1)
	{
		pipe(pp->pipe + 2 * i);
		i++;
	}
}

void	close_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < pp->pipe_nb)
	{
		close(pp->pipe[i]);
		i++;
	}
}

void	dup2_spe(int z, int f)
{
	dup2(z, 0);
	dup2(f, 1);
}

void	child(t_pp *pp, char *cmd, char **env)
{
	int	i;

	pp->pid = fork();
	if (pp->pid == 0)
	{
		if (pp->idx < pp->cmd_nb - 1)
			dup2_spe(pp->pipe[2 * pp->idx - 2], pp->pipe[2 * pp->idx + 1]);
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

void	wait_childs(int *pidtab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		waitpid(pidtab[i], NULL, 0);
}

int	ft_pipe(t_shell *shell, char **token)
{
	t_pp	pp;
	int		i;

	pp.cmd_nb = cmd_count(token);
	if (pp.cmd_nb == 1)
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
		child(&pp, token[i], shell->env);
		i += 2;
	}
	close_pipes(&pp);
	wait_childs(pp.pidtab, pp.cmd_nb);
	free(pp.pipe);
	free(pp.pidtab);
	return (1);
}
