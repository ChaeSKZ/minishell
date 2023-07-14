/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/13 23:15:15 by user42           ###   ########.fr       */
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
	shell->builtins[0] = strdup("echo"); // Remplacer par ft_strdup
	shell->builtins[1] = strdup("cd");
	shell->builtins[2] = strdup("pwd");
	shell->builtins[3] = strdup("export");
	shell->builtins[4] = strdup("unset");
	shell->builtins[5] = strdup("env");
	shell->builtins[6] = strdup("exit");
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
	int	pid;
	int	i;
	t_shell shell;
	
	init_shell(&shell);
	while (1)
	{
		i = -1;
		line = readline("$>");
		while (shell.builtins[++i])
		{
			if (mnsh_strcmp(shell.builtins[i], line) == 0)
			{
				printf("Found.\n");
				shell.f_ptr[i](get_args(line));
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				char *cmd[] = {"ls", NULL};
				char *envp[] = {NULL};
				execve(get_cmd(line), cmd, envp);
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
