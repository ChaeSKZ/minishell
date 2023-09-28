/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/27 14:32:26 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell, char *arg)
{
	char	cwd[MAX_PATH_SIZE];

	(void)arg;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("cwd");
	return ;
}

void	ft_unset(t_shell *shell, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		if (ft_envstrcmp(shell->env[i], arg) == 0)
		{
			j = i;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	ft_env(t_shell *shell, char *arg)
{
	int	i;

	i = -1;
	(void)arg;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return ;
}

int	ft_strcmp(char *str, char *env)
{
	int	x;

	x = 0;
	while (env[++x] != '=')
		if (env[x] != str[x])
			return (0);
	return (1);
}

char	*ft_str_eg_cpy(char *env)
{
	int		x;
	int		y;
	char	*str;

	x = -1;
	y = -1;
	while (env[++x] != '=')
		;
	str = malloc ((ft_strlen(str) - x) * sizeof(char));
	x++;
	while (env[x] != '\0')
	{
		str[y] = env[x];
		y++;
		x++;
	}
	str[y] = '\0';
	return (str);
}

char	*ft_ryoiki_tenkai(t_shell *shell, char *str)
{
	int	x;

	x = -1;
	while (shell->env[++x])
		if (ft_strcmp(str, shell->env[x]) == 1)
			return (free(str), str = ft_str_eg_cpy(shell->env[x]));
	return (NULL);
}

void	ft_echo(t_shell *shell, char *arg)
{
	int		x;
	int		y;
	int		n;
	char	**tab;

	(void)shell;
	tab = ft_split_quote(arg);
	if (tab == NULL)
		return ;
	x = 0;
	n = 0;
	y = -1;
	if (tab[x][0] == '-' && tab[x][1] == 'n')
	{
			x++;
			n = 1;
	}
	while (tab[x])
	{
		if (tab[x][0] == '$')
			tab[x] = ft_ryoiki_tenkai(shell, tab[x]);
		printf("%s", tab[x]);
		x++;
	}
	if (n != 1)
		printf("\n");
	return ;
}

/*
void	ft_echo(t_shell *shell, char *arg)
{
	int	x;
	int	y;
	char	**tab;
	char *arg2;

	(void)shell;
	tab = ft_split_quote(shell, arg);
	if (tab == NULL)
		return ;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		x = 1;
		y = -1;
		arg2 = malloc ((ft_strlen(arg) - 2) * sizeof (char));
		while (arg[x] == 'n')
			x++;
		while (++x < ft_strlen(arg))
			arg2[++y] = arg[x];
		arg2[++y] = '\0';
	}
	else
	{
		x = -1;
		arg2 = malloc ((ft_strlen(arg) + 1) * sizeof (char));
		while (++x < ft_strlen(arg))
			arg2[x] = arg[x];
		arg2[x] = '\0';
	}
	if (arg[0] == '-' && arg[1] == 'n')
		printf("%s", arg2);
	else
		printf("%s\n", arg2);
	free(arg2);
	return ;
}
*/

/*void	ft_echo(t_shell *shell, char *arg)
{
	int	x;
	int	y;
	char *arg2;

	(void)shell;
	arg = ft_split_quote(shell, arg);
	if (arg == NULL)
		return ;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		x = 1;
		y = -1;
		arg2 = malloc ((ft_strlen(arg) - 2) * sizeof (char));
		while (arg[x] == 'n')
			x++;
		while (++x < ft_strlen(arg))
			arg2[++y] = arg[x];
		arg2[++y] = '\0';
	}
	else
	{
		x = -1;
		arg2 = malloc ((ft_strlen(arg) + 1) * sizeof (char));
		while (++x < ft_strlen(arg))
			arg2[x] = arg[x];
		arg2[x] = '\0';
	}
	if (shell->meta[0] == 2 || shell->meta[0] == 1)
		printf("%s", arg2);
	else
	{
		x = -1;
		while (++x < ft_strlen(arg2))
		{
			if ((arg2[x] == 92 && arg2[x + 1] == 110) && ((x + 1) == ft_strlen(arg2) - 1))
			{
				arg2[x] = 'n';
				arg2[x + 1] = '\0';
			}
			if (arg2[x] == 92 && arg2[x + 1] == 110)
			{
				arg2[x] = 'n';
				x = x + 1;
			}
		}
		printf("%s", arg2);
	}
	free(arg2);
	return ;
}*/
