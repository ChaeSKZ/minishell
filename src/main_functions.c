/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:18:08 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 10:59:23 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_core2(t_shell *shell, int status)
{
	shell->pid = fork();
	signal(SIGQUIT, SIG_DFL);
	if (shell->pid == 0)
	{
		check_redirect(shell->tokens[0]);
		execve(get_cmd(shell->tokens[0]),
			ignore_redirections(ft_split(shell->tokens[0], ' ')),
			shell->env);
		printf("%s: command not found\n", get_cmd(shell->tokens[0]));
		exit(127);
	}
	else if (shell->pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		if (ft_strncmp(shell->tokens[0], "./minishell", 11) == 0)
			signal(SIGINT, SIG_IGN);
		waitpid(shell->pid, &status, 0);
		init_signals();
	}
	else
		perror("fork");
	if (WIFEXITED(status))
		shell->errno = WEXITSTATUS(status);
}

void	main_core(t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_strlen(shell->line))
		if (!ft_pipe(shell) && call_builtins(shell, 0, 0, 0) == 7)
			main_core2(shell, status);
}

void	prompt(t_shell *shell)
{
	if (!shell->errno)
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" GREEN "OK" RESET "] " BLUE "$> " RESET);
	else
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" RED "KO" RESET "] " BLUE "$> " RESET);
}
