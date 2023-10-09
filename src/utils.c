/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:51 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/09 15:32:17 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	power_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	mnsh_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i + 1] != ' '
		&& s2[i + 1] != ' ' && s1[i] == s2[i] && s2[i] != '\n')
		i++;
	return (s1[i] - s2[i]);
}

char	*get_args(char *line)
{
	char	*arg;
	int		i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		arg = line + i + 1;
	else
		arg = NULL;
	return (arg);
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
	else
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
	}
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

char	*get_cmd_name(char *line)
{
	int		i;
	char	*cmd;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * i);
	if (!cmd)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (line[i] && line[i] == ' ')
	{
		cmd[i] = line[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}
