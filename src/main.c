/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/09 13:54:45 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	shell->errno = 0;
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

int	call_builtins(t_shell *shell, int is_in)
{
	int	i;

	i = -1;
	while (ft_strlen(shell->line) && shell->builtins[++i])
	{
		if (is_in && mnsh_strcmp(shell->builtins[i], "env") == 0)
			i++;
		if (mnsh_strcmp(shell->builtins[i], shell->line) == 0)
		{
			shell->errno = shell->f_ptr[i](shell, get_args(shell->line));
			return(i);
		}
	}
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		i;
	int		status = 0;

	init_shell(&shell, env);
	shell.envp[0] = NULL;
	while (ac && av[0])
	{
		i = -1;
		prompt(&shell);
		if (shell.line == NULL)
			ft_exit(&shell, NULL);
		add_history(shell.line);
		shell.tokens = epur_tab(ft_split(shell.line, '|'));
		// while (ft_strlen(shell.line) && shell.builtins[++i])
		// {
		// 	if (mnsh_strcmp(shell.builtins[i], shell.line) == 0)
		// 	{
		// 		shell.errno = shell.f_ptr[i](&shell, get_args(shell.line));
		// 		break ;
		// 	}
		// }
		if (ft_strlen(shell.line) && call_builtins(&shell, 0) == 7)
		{
			if (!ft_pipe(&shell, shell.tokens))
			{
				shell.pid = fork();
				if (shell.pid == 0)
				{
					/*char	**tab;
					tab = ft_split_quote(shell.tokens[0]);
					printf("test : %s\n", tab[0]);*/
					check_redirect(shell.tokens[0]);
					execve(get_cmd(shell.tokens[0]), ignore_redirections(ft_split(shell.tokens[0], ' ')),
						shell.env);
					printf("%s: command not found\n", get_cmd(shell.tokens[0]));
					exit(127);
				}
				else if (shell.pid > 0)
					waitpid(shell.pid, &status, 0);
				else
					perror("fork");
				if (WIFEXITED(status))
				{
					shell.errno = WEXITSTATUS(status);
				}
			}
		}
		printf("Exited with error code : %i\n", shell.errno);
		power_free(shell.tokens);
		//free(shell.meta);
	}
	return (0);
}
