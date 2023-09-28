/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/28 11:56:52 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_pp *pp, char *cmd, char **env, char **next)
{
	int	i;
	int	fd;

	pp->pid = fork();
	fd = 0;
	(void)next;
	if (pp->pid == 0)
	{
		if (pp->idx == 0)
			dup2_spe(STDIN_FILENO, pp->pipe[1]);
		else if (pp->idx < pp->cmd_nb - 1)
			dup2_spe(pp->pipe[2 * pp->idx - 2], pp->pipe[2 * pp->idx + 1]);
		else
			dup2_spe(pp->pipe[2 * pp->idx - 2], STDOUT_FILENO);
		close_pipes(pp);
		execve(get_cmd(cmd), ft_split(cmd, ' '), env);
		perror("execve");
		exit(0);
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
	if (!pp->pipe_nb)
		wait(NULL);
	while (++i < pp->pipe_nb - 1)
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
