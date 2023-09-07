/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/07 11:47:17 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child1(int *pipe_fd, char *cmd, char **env)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execve(get_cmd(cmd), ft_split(cmd, ' '), env);
	//perror("execve");
}

void	child2(int *pipe_fd, char *cmd, char **env)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execve(get_cmd(cmd), ft_split(cmd, ' '), env);
	//perror("execve");
}

void	close_wait(int *pipe_fd, int cmd_pid1, int cmd_pid2)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(cmd_pid1, NULL, 0);
	waitpid(cmd_pid2, NULL, 0);
}

int		ft_pipe(t_shell *shell, char **token)
{
	int		pipe_fd[2];
	pid_t	cmd_pid1;
	pid_t	cmd_pid2;

	cmd_pid2 = 0;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 0);
	cmd_pid1 = fork();
	if (cmd_pid1 == -1)
		return (perror("fork"), 0);
	if (cmd_pid1 == 0)
		child1(pipe_fd, token[0], shell->env);
	cmd_pid2 = fork();
	if (cmd_pid2 == -1)
		return (perror("fork"), 0);
	if (cmd_pid2 == 0)
		child2(pipe_fd, token[2], shell->env);
	close_wait(pipe_fd, cmd_pid1, cmd_pid2);
	return (0);
}
