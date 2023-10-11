/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:03:36 by jquil             #+#    #+#             */
/*   Updated: 2023/10/09 14:16:11 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == '=' || s2[i] == '=')
		return (0);
	return (s1[i] - s2[i]);
}

char	*get_home_path(char **env)
{
	int		i;
	int		n;
	char	*path;

	i = 0;
	while (ft_envstrcmp(env[i], "HOME"))
		i++;
	n = 0;
	while (env[i][n + 5])
		n++;
	path = malloc(sizeof(char) * (n + 1));
	if (!path)
	{
		perror("malloc");
		return (0);
	}
	n = 0;
	while (env[i][n + 5])
	{
		path[n] = env[i][n + 5];
		n++;
	}
	path[n] = '\0';
	return (path);
}

char	**init_sep(void)
{
	char	**sep;

	sep = malloc(sizeof(char *) * 6);
	if (!sep)
		perror("malloc");
	sep[0] = ft_strdup("|");
	sep[1] = ft_strdup(">");
	sep[2] = ft_strdup(">>");
	sep[3] = ft_strdup("<");
	sep[4] = ft_strdup("<<");
	sep[5] = NULL;
	return (sep);
}
