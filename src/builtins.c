/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:40:26 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 17:03:23 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, char *arg)
{
	char	cwd[MAX_PATH_SIZE];

	(void)shell;
	(void)arg;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("cwd");
	return (0);
}

int	ft_exit(t_shell *shell, char *arg)
{
	(void)arg;
	if (shell->builtins)
		power_free(shell->builtins);
	if (shell->tokens)
		power_free(shell->tokens);
	if (shell->line)
		free(shell->line);
	if (shell->env)
		power_free(shell->env);
	if (!arg || !ft_strlen(arg))
	{
		printf("exit\n");
		return (exit(0), 0);
	}
	exit(127);
}

char	*check_path(char *path)
{
	int		i;
	char	*new_path;

	if ((path[0] == '.' && path[1] == '/')
		|| path[0] == '/')
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
	return (new_path);
}

char	*path_copy(char *dest, char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		perror("malloc");
	i = 0;
	while (path[i])
	{
		dest[i] = path[i];
		i++;
	}
	return (dest);
}

int	ft_cd(t_shell *shell, char *path)
{
	char	*temp;

	temp = NULL;
	if (!path || (((path[0] == '~' && path[1] == '/')
				|| (path[0] == '-' && path[1] == '-')) && !path[2]))
		chdir(get_home_path(shell->env));
	else if (path[0] == '/' && !path[1])
		chdir("/");
	else if (path[0] == '-' && !path[1])
	{
		temp = path_copy(temp, shell->ex_path);
		printf("%s\n", shell->ex_path);
		getcwd(shell->ex_path, sizeof(shell->ex_path));
		chdir(temp);
	}
	else
	{
		path = check_path(path);
		getcwd(shell->ex_path, sizeof(shell->ex_path));
		if (chdir(path) == -1)
			return (perror("chdir"), 1);
		free(path);
	}
	return (0);
}
