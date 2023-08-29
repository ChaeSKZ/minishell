/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:07:17 by jugingas          #+#    #+#             */
/*   Updated: 2023/08/29 16:36:39 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	check_sep(char *str, char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (mnsh_strcmp(sep[i], str) == 0)
		{
			printf("found : %s\n", sep[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	token_len(char *str, char **sep)
{
	int	i;

	i = 0;
	while (str[i] && (check_sep(str + i, sep) && str[i - 1] == ' '))
		i++;
	printf("Token lenght is : %i\n", i);
	return (i);
}

char	**token_it2(char *str, int count, char **sep)
{
	char	**tokens;
	int		i;
	int		n;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		perror("malloc");
	n = 0;
	i = 0;
	while (str[i])
	{
		tokens[n] = malloc(sizeof(char) * (token_len(str + i, sep) + 1));
		if (!tokens[n])
			perror("malloc");
	}
	return (tokens);
}

char	**token_it(char *str)
{
	char	**sep;
	int		i;
	int		count;

	sep = init_sep();
	i = 0;
	count = 1;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		if (check_sep(str + i, sep))
			count += 2;
		while (str[i] != ' ' && str[i + 1])
			i++;
		i++;
	}
	return (token_it2(str, count, sep));
}
