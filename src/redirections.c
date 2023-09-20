/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:29:10 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/20 17:05:53 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_right(char *filename)
{
	int	fd;

	printf("redirecting to \"%s\"...\n", filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	double_right(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	simple_left(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("open"), 0);
	return (fd);
}

int	double_left(char *cmd, char *delimiter, char **env)
{
	char	*heredoc;
	size_t	buffersize;
	int		pipe_fd[2];
	int		pid;

	heredoc = NULL;
	buffersize = 0;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 0);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror("fork"), 0);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], 0) == -1)
		{
			close(pipe_fd[0]);
			return (perror("dup2"), 0);
		}
		execve(get_cmd(cmd), ft_split(cmd, ' '), env);
		perror("execve");
		close(pipe_fd[0]);
		exit(0);
	}
	else
	{
		close(pipe_fd[0]);
		heredoc = get_heredoc(delimiter);
		write(pipe_fd[1], heredoc, ft_strlen(heredoc));
		close(pipe_fd[1]);
		wait(NULL);
		free(heredoc);
	}
	return (0);
}
