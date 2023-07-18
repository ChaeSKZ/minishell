/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/18 11:57:13 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/minishell.h"

void	init_shell(t_shell *shell)
{
	shell->builtins = malloc(sizeof(char *) * 8);
	if (!shell->builtins)
	{
		perror("malloc");
		exit(1);
	}
	shell->builtins[0] = ft_strdup("echo");
	shell->builtins[1] = ft_strdup("cd");
	shell->builtins[2] = ft_strdup("pwd");
	shell->builtins[3] = ft_strdup("export");
	shell->builtins[4] = ft_strdup("unset");
	shell->builtins[5] = ft_strdup("env");
	shell->builtins[6] = ft_strdup("exit");
	shell->builtins[7] = NULL;
	shell->f_ptr[0] = ft_echo;
	shell->f_ptr[1] = ft_cd;
	shell->f_ptr[2] = ft_pwd;
	shell->f_ptr[3] = ft_export;
	shell->f_ptr[4] = ft_unset;
	shell->f_ptr[5] = ft_env;
	shell->f_ptr[6] = ft_exit;
}

int	main(void)
{
	char	*line;
	int		pid;
	int		i;
	t_shell	shell;
	char	*envp[1];

	init_shell(&shell);
	envp[0] = NULL;
	while (1)
	{
		i = -1;
		line = readline("$>");
		while (shell.builtins[++i])
		{
			if (mnsh_strcmp(shell.builtins[i], line) == 0)
			{
				shell.f_ptr[i](get_args(line));
				break ;
			}
		}
		if (i == 7)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(get_cmd(line), ft_split(line, ' '), envp);
				perror("execve");
			}
			else if (pid > 0)
				wait(NULL);
			else
				perror("fork");
		}
	}
	return (0);
}
