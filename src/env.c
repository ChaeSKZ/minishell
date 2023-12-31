/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:12:36 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/24 14:32:34 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*itoa_2(char *str, int nb, int len)
{
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str += len;
	*str = '\0';
	while (nb != 0)
	{
		*--str = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
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

	return (itoa_2(str, nb, len));
}

char	**copy_env(char **env)
{
	int		i;
	int		n;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (tab_len(env) + 1));
	if (!new)
		return (perror("malloc"), NULL);
	while (env[++i] != NULL)
	{
		n = -1;
		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new[i])
			return (perror("malloc"), new);
		while (env[i][++n])
			new[i][n] = env[i][n];
		new[i][n] = '\0';
	}
	new[i] = NULL;
	return (new);
}

void	init_env(t_shell *shell, char **env)
{
	int		i;
	char	*str;
	char	*shlvl;
	char	*ito;

	i = 0;
	if (env[0])
	{
		shell->env = copy_env(env);
		while (ft_envstrcmp(env[i], "SHLVL="))
			i++;
		str = get_value(env[i]);
		shlvl = ft_strdup("SHLVL=");
		ito = itoa(atoi(str) + 1);
		update_env(str_add(shlvl, ito, 0, 0), shell);
		free(shlvl);
		free(ito);
		free(str);
	}
	else
		create_env(shell);
}
