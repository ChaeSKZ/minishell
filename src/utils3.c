/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:03:36 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 11:23:25 by jugingas         ###   ########.fr       */
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

char	*init_cmd(char *cmd, int i)
{
	cmd = malloc(sizeof(char) * (i + 6));
	if (!cmd)
		return (perror("malloc"), NULL);
	cmd[0] = '/';
	cmd[1] = 'b';
	cmd[2] = 'i';
	cmd[3] = 'n';
	cmd[4] = '/';
	cmd[i + 5] = '\0';
	return (cmd);
}

char	*get_cmd(char *line)
{
	int		i;
	char	*cmd;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if ((line[0] == '.' && line[1] == '/')
		|| line[0] == '/')
		return (line);
	cmd = NULL;
	cmd = init_cmd(cmd, i);
	if (!cmd)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (line[i] && line[i] != ' ')
	{
		cmd[i + 5] = line[i];
		i++;
	}
	return (cmd);
}
