/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/07 11:57:42 by jquil            ###   ########.fr       */
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
	init_signals();
	shell->env = env;
	getcwd(shell->ex_path, sizeof(shell->ex_path));
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

char	*get_cwd(void)
{
	int		i;
	int		n;
	char	cwd[MAX_PATH_SIZE];
	char	*res;

	i = 0;
	n = 1;
	getcwd(cwd, sizeof(cwd));
	while (cwd[i])
		i++;
	while (cwd[i - n] != '/')
		n++;
	i -= n;
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		perror("malloc");
	n = 0;
	while (cwd[i + n + 1])
	{
		res[n] = cwd[i + n + 1];
		n++;
	}
	res[n] = '\0';
	return (res);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		i;

	init_shell(&shell, env);
	shell.envp[0] = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		i = -1;
		/*printf("\033[1;32m");			// Pimped prompt
		printf("%s", get_cwd());
		printf("\033[0m");
		printf("~> ");*/
		shell.line = readline("$>");
		if (shell.line == NULL)
			ft_exit(&shell, get_args(shell.line));
		add_history(shell.line);
		token_it(shell.line);
		ft_split_quote(&shell, get_args(shell.line));
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
				execve(get_cmd(shell.line), ft_split(shell.line, ' '),
				shell.env);
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
