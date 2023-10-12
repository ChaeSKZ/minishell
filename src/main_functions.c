/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:18:08 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/12 19:29:30 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *str)
{
	int	i;

	i = 0;
	if (!str[1])
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '>'
			&& str[i] != '<' && str[i] != '|')
			return (1);
		i++;
		if (str[i] && (str[i] == '>' && str[i] == '<' && str[i] == '|'))
			return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	}
	return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
}
int	check_redirects(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'))
		i++;
	if ((str[0] == '>' && str[1] == '<')
		|| (str[0] == '<' && str[1] == '>'))
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	if (!str[i + 1])
		return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '>'
			&& str[i] != '<' && str[i] != '|')
			return (1);
		i++;
		if (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
	}
	return (printf("unexpected error near token \'%c\'\n", str[0]), 0);
}

int	check_before(char *str, int idx)
{
	int	i;

	i = -1;
	while (str[++i] && i < idx)
	{
		if (str[i] != ' ' && str[i] != '|'
			&& str[i] != '>' && str[i] != '<')
			return (1);
	}
	return (printf("unexpected error near token \'%c\'\n", str[idx]), 0);
}

int	badline(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && !check_pipes(str + i))
			return (2);
		if ((str[i] == '>' || str[i] == '<') && !check_redirects(str + i))
			return (2);
		if (str[i] == '>' || str[i] == '<')
			i++;
	}
	return (0);
}

void	main_core(t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_strlen(shell->line))
	{
		if (!ft_pipe(shell) && call_builtins(shell, 0, 0, 0) == 7)
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
