/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:12:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/28 16:24:02 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_add(char *str, char *add)
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
	env[0] = str_add(env[0], cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	shell->env = env;
}

char	*get_value(char *str)
{
	int		i;
	int		len;
	char	*new;
	int		n;

	i = 0;
	len = -1;
	while (str[i] && str[i] != '=')
		i++;
	while (str[i + 1 + ++len])
		;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (perror("malloc"), NULL);
	n = 0;
	while (str[++i])
	{
		new[n] = str[i];
		n++;
	}
	new[n] = '\0';
	return (new);
}

char	*itoa(int nb)
{
	int		len;
	int		temp;
	char	*str;

	temp = nb / 10;
	len = 1;
	while (temp)
	{
		len++;
		temp /= 10;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (perror("malloc"), NULL);
	str += len;
	*str = '\0';
	while (nb != 0)
	{
		*--str = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}

void	init_env(t_shell *shell, char **env)
{
	int	i;
	
	i = 0;
	if (env[0])
	{
		shell->env = env;
		while (ft_envstrcmp(env[i], "SHLVL=Gros Crane Chauve"))
			i++;
		update_env(str_add("SHLVL=", itoa(atoi(get_value(env[i])) + 1)), shell);
	}
	else
		create_env(shell);
}
