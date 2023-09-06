/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:21:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/06 19:32:19 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pipe(t_shell *shell, char **token)
{
	int		pipe_fd[2];
	pid_t	cmd_pid1;
	pid_t	cmd_pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	cmd_pid1 = fork();
	if (cmd_pid1 == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(get_cmd(token[0]), ft_split(token[0], ' '), shell->env);
	}
	else
	{
		cmd_pid2 = fork();
		if (cmd_pid2 == 0)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			execve(get_cmd(token[2]), ft_split(token[2], ' '), shell->env);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
	return (0);
}
