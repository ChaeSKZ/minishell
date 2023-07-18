/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:51 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/18 11:38:53 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		arg = line + i + 1;
	else if (!line[i] || line[i] == '\n')
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
	cmd = malloc(sizeof(char) * i + 5);
	cmd[0] = '/';
	cmd[1] = 'b';
	cmd[2] = 'i';
	cmd[3] = 'n';
	cmd[4] = '/';
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
	cmd[i + 5] = '\0';
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
