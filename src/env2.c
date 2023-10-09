/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:10:27 by jquil             #+#    #+#             */
/*   Updated: 2023/10/09 14:10:44 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_add(char *str, char *add, int fr)
{
	int		i;
	int		s;
	int		a;
	char	*new;

	i = 0;
	s = -1;
	a = -1;
	new = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(add) + 1));
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
	if (fr)
		free(add);
	return (new);
}

void	create_env(t_shell *shell)
{
	char	**env;
	char	cwd[MAX_PATH_SIZE];

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return ((void)perror("malloc"));
	getcwd(cwd, sizeof(cwd));
	env[0] = ft_strdup("PWD=");
	env[0] = str_add(env[0], cwd, 0);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	shell->env = env;
}
