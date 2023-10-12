/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/12 19:31:37 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(char *cmd)
{
	char	**cmdtab;
	int		i;
	int		fd;

	cmdtab = ft_split(cmd, ' ');
	i = -1;
	fd = 0;
	while (cmdtab[++i])
		fd = redirect(cmdtab, i);
	return (power_free(cmdtab), fd);
}

void	child(t_pp *pp, t_shell *shell, char *cmd, int idx)
{
	int		i;
	char	**no_redirec;
	char	*cmd_name;
	char	**tab;

	tab = ft_split(cmd, ' ');
	no_redirec = ignore_redirections(tab);
	cmd_name = get_cmd(cmd);
	pp->pid = fork();
	if (pp->pid == 0)
	{
		if (pp->idx == 0)
			dup2_spe(STDIN_FILENO, pp->pipe[1]);
		else if (pp->idx < pp->cmd_nb - 1)
			dup2_spe(pp->pipe[2 * pp->idx - 2], pp->pipe[2 * pp->idx + 1]);
		else
			dup2_spe(pp->pipe[2 * pp->idx - 2], STDOUT_FILENO);
		close_pipes(pp);
		if (call_builtins(shell, 0, 1, idx) == 7)
		{
			check_redirect(cmd);
			execve(cmd_name, no_redirec, shell->env);
			printf("%s: command not found\n", cmd);
			exit(127);
		}
	}
	else
	{
		i = -1;
		while (++i < pp->cmd_nb - 1 && pp->pidtab[i] != 0)
			;
		pp->pidtab[i] = pp->pid;
	}
	//power_free(no_redirec);
	free(cmd_name);
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

void	wait_childs(t_pp *pp, t_shell *shell)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pp->cmd_nb)
	{
		waitpid(pp->pidtab[i], &status, 0);
		if (WIFEXITED(status))
			shell->errno = WEXITSTATUS(status);
	}
	free(pp->pipe);
	free(pp->pidtab);
}

int	ft_pipe(t_shell *shell)
{
	t_pp	pp;
	int		i;

	pp.cmd_nb = cmd_count(shell->tokens);
	if (pp.cmd_nb == 1 && !shell->tokens[1])
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
		child(&pp, shell, shell->tokens[i], i);
		i++;
	}
	close_pipes(&pp);
	wait_childs(&pp, shell);
	return (1);
}
