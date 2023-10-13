/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:03:36 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 18:23:59 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
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

char	*init_cmd(char *cmd, char **env)
{
	char			**tab;
	int				i;
	DIR				*d;
	struct dirent	*dir;
	char			*val;

	i = 0;
	while (env[i] && ft_envstrcmp(env[i], "PATH="))
		i++;
	if (!env[i])
		return (NULL);
	val = get_value(env[i]);
	tab = ft_split(val, ':');
	i = -1;
	while (tab[++i])
	{
		d = opendir(tab[i]);
		if (d)
		{
			dir = readdir(d);
			while (dir != NULL)
			{
				if (ft_strncmp(cmd, dir->d_name, ft_strlen(dir->d_name)) == 0)
				{
					free(val);
					val = ft_strdup(tab[i]);
					power_free(tab);
					return (str_add(
							str_add(val, "/", 1, 0), dir->d_name, 1, 0));
				}
				dir = readdir(d);
			}
		}
		closedir(d);
	}
	free(val);
	power_free(tab);
	return (NULL);
}

char	*get_cmd(char *line, char **env)
{
	char	*cmd;
	char	**tab;

	if (((line[0] == '.' || line[0] == '~') && line[1] == '/')
		|| line[0] == '/')
		return (line);
	cmd = NULL;
	tab = ft_split(line, ' ');
	cmd = init_cmd(tab[0], env);
	if (!cmd)
		cmd = ft_strcpy(tab[0], cmd);
	if (tab)
		power_free(tab);
	return (cmd);
}
