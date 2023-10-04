/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/04 13:24:27 by jugingas         ###   ########.fr       */
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
	new = malloc(sizeof(char*) * tab_len(tab) + 1);
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
			n++;
			new[n] = NULL;
			i++;
		}
	}
	return (new);
}

void	check_redirect(char *cmd)
{
	char	**cmdtab;
	int		i;
	int		fd;

	cmdtab = ft_split(cmd, ' ');
	i = -1;
	fd = 0;
	while (cmdtab[++i])
	{
		if (!ft_strncmp(cmdtab[i], ">", 1) && cmdtab[i + 1])
		{
			fd = simple_right(cmdtab[i + 1]);
			dup2(fd, STDOUT_FILENO);
		}
		if (!ft_strncmp(cmdtab[i], ">>", 1) && cmdtab[i + 1])
		{
			fd = double_right(cmdtab[i + 1]);
			dup2(fd, STDOUT_FILENO);
		}
		if (!ft_strncmp(cmdtab[i], "<", 1) && cmdtab[i + 1])
		{
			fd = simple_left(cmdtab[i + 1]);
			dup2(fd, STDIN_FILENO);
		}
	}
}

void	child(t_pp *pp, char *cmd, char **env, char **next)
{
	int	i;
	char	**no_redirec;
	char	*cmd_name;

	no_redirec = ignore_redirections(ft_split(cmd, ' '));
	cmd_name = get_cmd(cmd);
	pp->pid = fork();
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
		check_redirect(cmd);
		execve(cmd_name, no_redirec, env);
		perror("execve");
		exit(0);
	}
	else
	{
		i = -1;
		while (++i < pp->cmd_nb - 1 && pp->pidtab[i] != 0)
			;
		pp->pidtab[i] = pp->pid;
	}
 	free(no_redirec);
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
	wait(NULL);
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
		i++;
	}
	close_pipes(&pp);
	wait_childs(&pp);
	return (1);
}
