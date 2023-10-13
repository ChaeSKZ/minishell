/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:57:38 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 15:59:49 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			equal++;
		i++;
	}
	if (equal != 1)
		return (0);
	return (1);
}

int	check_exist(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_envstrcmp(shell->env[i], arg))
			return (1);
		i++;
	}
	return (0);
}

void	add_env(char *arg, t_shell *shell)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = ft_calloc((i + 2), sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		return ;
	}
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	new_env[i] = ft_strcpy(arg, new_env[i]);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return ;
}

void	update_env(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	while (ft_envstrcmp(arg, shell->env[i]))
		i++;
	free(shell->env[i]);
	shell->env[i] = ft_strdup(arg);
	free(arg);
	return ;
}

int	ft_export(t_shell *shell, char *arg)
{
	char	**args;
	int		i;

	args = NULL;
	if (arg == NULL)
		return (0);
	else
	{
		args = ft_split(arg, ' ');
		i = 0;
		while (args[i])
		{
			if (check_arg(args[i]))
			{
				if (!check_exist(args[i], shell))
					add_env(args[i], shell);
				else
					update_env(args[i], shell);
			}
			i++;
		}
	}
	power_free(args);
	return (0);
}
