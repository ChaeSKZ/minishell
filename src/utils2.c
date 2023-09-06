/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:07:17 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/06 18:01:29 by jugingas         ###   ########.fr       */
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

int	check_sep(char *str, char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (mnsh_strcmp(sep[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**init_tok(char *str, char **sep, char **tokens)
{
	int	i;
	int	size;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		size = 0;
		if (n % 2 == 0)
		{
			while (str[i + size])
			{
				size++;
				if (str[i + size - 1] == ' ' && check_sep(str + i + size, sep))
					break ;
			}
			i += size;
		}
		else
		{
			while (str[i + size] != ' ' && str[i + size])
				size++;
			i += size;
		}
		tokens[n] = malloc(sizeof(char) * (size + 1));
		n++;
	}
	return (tokens);
}

char	**copy_tok(char *str, char **sep, char **tokens)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	i = 0;
	while (str[i])
	{
		j = -1;
		if (n % 2 == 0)
		{
			while (str[i])
			{
				tokens[n][++j] = str[i];
				i++;
				if (str[i] == ' ' && check_sep(str + i + 1, sep))
				{
					i++;
					break ;
				}
			}
		}
		else
		{
			while (str[i] && str[i] != ' ')
			{
				tokens[n][++j] = str[i];
				i++;
			}
			i++;
		}
		n++;
	}
	tokens[n] = NULL;
	return (tokens);
}

char	**token_it2(char *str, int count, char **sep)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		perror("malloc");
	tokens = init_tok(str, sep, tokens);
	tokens = copy_tok(str, sep, tokens);
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
