/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:18:08 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/09 18:47:45 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_core(t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_strlen(shell->line))
		{
			if (!ft_pipe(shell) && call_builtins(shell, 0, 0, 0) == 7)
			{
				shell->pid = fork();
				if (shell->pid == 0)
				{
					check_redirect(shell->tokens[0]);
					execve(get_cmd(shell->tokens[0]), ignore_redirections(ft_split(shell->tokens[0], ' ')),
						shell->env);
					printf("%s: command not found\n", get_cmd(shell->tokens[0]));
					exit(127);
				}
				else if (shell->pid > 0)
					waitpid(shell->pid, &status, 0);
				else
					perror("fork");
				if (WIFEXITED(status))
					shell->errno = WEXITSTATUS(status);
			}
		}
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
