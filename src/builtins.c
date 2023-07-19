/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:40:26 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/19 09:49:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_shell *shell, char *arg)
{
	(void)arg;
	power_free(shell->builtins);
	free(shell->line);
	exit(0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	i++;
	return (i);
}

char	*check_path(char *path)
{
	int		i;
	char	*new_path;

	if ((path[0] == '.' && path[1] == '/')
		|| (path[0] == '~' && path[1] == '/') || path[0] == '/')
		return (path);
	i = -1;
	new_path = malloc(sizeof(char) * ft_strlen(path) + 3);
	if (!new_path)
	{
		perror("malloc");
		exit (0);
	}
	new_path[0] = '.';
	new_path[1] = '/';
	while (path[++i])
		new_path[i + 2] = path[i];
	new_path[i + 2] = '\0';
	free(path);
	return (new_path);
}

void	ft_cd(t_shell * shell, char *path)
{
	(void)shell;
	if (!path)
		chdir("~/");
	else
	{
		path = check_path(path);
		chdir(path);
		free(path);
	}
}

void	ft_echo(t_shell *shell, char *arg)
{
	(void)arg;
	(void)shell;
	return ;
}

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
	return ;
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
