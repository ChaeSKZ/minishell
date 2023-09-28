/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/28 17:47:20 by jquil            ###   ########.fr       */
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
	{
		if (ft_envstrcmp(str + 1, shell->env[x]) == 0)
			return (free(str), str = ft_str_eg_cpy(shell->env[x]));
	}
	return (NULL);
}

void	ft_echo(t_shell *shell, char *arg)
{
	int		x;
	int		y;
	int		n;

	shell->tab = ft_split_quote(arg);
	if (shell->tab == NULL)
		return ;
	x = 0;
	n = 0;
	y = -1;
	if (shell->tab[x][0] == '-' && shell->tab[x][1] == 'n')
	{
			x++;
			n = 1;
	}
	while (shell->tab[x])
	{
		if (shell->tab[x][0] == '$')
			shell->tab[x] = ft_ryoiki_tenkai(shell, shell->tab[x]);
		printf("tab[x] = %s\n", shell->tab[x]);
		x++;
	}
	if (n != 1)
		printf("\n");
	return ;
}
