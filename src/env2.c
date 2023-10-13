/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:10:27 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 11:25:14 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_free(char *str, char *add, int fr_str, int fr_add)
{
	if (fr_add)
		free(add);
	if (fr_str)
		free(str);
}

char	*str_add(char *str, char *add, int fr_str, int fr_add)
{
	int		i;
	int		s;
	int		a;
	char	*new;

	i = 0;
	s = -1;
	a = -1;
	new = ft_calloc((ft_strlen(str) + ft_strlen(add) + 1), sizeof(char));
	if (!new)
		return (perror("malloc"), NULL);
	while (str[++s])
	{
		new[i] = str[s];
		i++;
	}
	while (add[++a])
	{
		new[i] = add[a];
		i++;
	}
	new[i] = '\0';
	check_free(str, add, fr_str, fr_add);
	return (new);
}

void	create_env(t_shell *shell)
{
	char	**env;
	char	cwd[MAX_PATH_SIZE];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return ((void)perror("malloc"));
	getcwd(cwd, sizeof(cwd));
	env[0] = ft_strdup("PWD=");
	env[0] = str_add(env[0], cwd, 0, 0);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	shell->env = env;
}

int	ft_unset(t_shell *shell, char *arg)
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
				free(shell->env[j]);
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_env(t_shell *shell, char *arg)
{
	int		i;

	i = -1;
	(void)arg;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return (0);
}
