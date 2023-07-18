/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/18 13:52:52 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->builtins = malloc(sizeof(char *) * 8);
	if (!shell->builtins)
	{
		perror("malloc");
		exit(1);
	}
	shell->env = env;
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

/*void	loop(t_shell *shell)
{
	int	i;

	while (1)
	{
		shell->line = ft_split(readline("$>"), ' ');
		i = -1;
		while (shell->builtins[++i])
		{
			if (mnsh_strcmp(shell.builtins[i], shell.line[0]) == 0)
			{
				shell.f_ptr[i](&shell, get_args(shell.line));
				break ;
			}
		}
	}
	return ;
}*/

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		i;

	init_shell(&shell, env);
	shell.envp[0] = NULL;
	(void)ac;
	(void)av;
	//loop(&shell);
	while (1)
	{
		i = -1;
		shell.line = readline("$>");
		while (shell.builtins[++i])
		{
			if (mnsh_strcmp(shell.builtins[i], shell.line) == 0)
			{
				shell.f_ptr[i](&shell, get_args(shell.line));
				break ;
			}
		}
		if (i == 7)
		{
			shell.pid = fork();
			if (shell.pid == 0)
			{
				execve(get_cmd(shell.line), ft_split(shell.line, ' '), shell.envp);
				perror("execve");
			}
			else if (shell.pid > 0)
				wait(NULL);
			else
				perror("fork");
		}
	}
	return (0);
}
