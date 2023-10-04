/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/04 10:39:51 by jugingas         ###   ########.fr       */
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
	init_env(shell, env);
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%i] : %s\n", i, tab[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		i;

	init_shell(&shell, env);
	shell.envp[0] = NULL;
	(void)ac;
	(void)av;
	//display_usage(ac, av):
	while (1)
	{
		i = -1;
		shell.line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" GREEN "OK" RESET "] " BLUE "$> " RESET);
		if (shell.line == NULL)
			ft_exit(&shell, get_args(shell.line));
		add_history(shell.line);
		shell.tokens = epur_tab(ft_split(shell.line, '|'));
		while (ft_strlen(shell.line) && shell.builtins[++i])
		{
			if (mnsh_strcmp(shell.builtins[i], shell.line) == 0)
			{
				shell.f_ptr[i](&shell, get_args(shell.line));
				break ;
			}
		}
		if (ft_strlen(shell.line) && i == 7)
		{
			if (!ft_pipe(&shell, shell.tokens))
			{
				shell.pid = fork();
				if (shell.pid == 0)
				{
					execve(get_cmd(shell.tokens[0]), ignore_redirections(ft_split(shell.tokens[0], ' ')),
						shell.env);
					perror("execve");
					exit(0);
				}
				else if (shell.pid > 0)
					wait(NULL);
				else
					perror("fork");
			}
		}
		power_free(shell.tokens);
		//free(shell.meta);
	}
	return (0);
}
