/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:38:51 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 11:20:00 by jugingas         ###   ########.fr       */
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
