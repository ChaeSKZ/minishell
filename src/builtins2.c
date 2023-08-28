/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/08/28 17:08:11 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_shell *shell, char *arg)
{
	char	cwd[MAX_PATH_SIZE];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("cwd");
		ft_exit(shell, arg);
	}
	(void)arg;
	return ;
}

void	ft_unset(t_shell *shell, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		if (ft_envstrcmp(shell->env[i], arg) == 0)
		{
			j = i;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	ft_env(t_shell *shell, char *arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return ;
}

void	ft_echo(t_shell *shell, char *arg)
{
	(void)arg;
	(void)shell;
	return ;
}
