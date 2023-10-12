/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/12 14:21:18 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char *arg)
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
				free(shell->env[j]);
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_env(t_shell *shell, char *arg)
{
	int		i;
	int		pid;
	int		status;
	char	**args;

	i = -1;
	pid = 0;
	status = 0;
	args = ft_split(arg, ' ');
	if (arg && args[0][0] != '|' && args[0][0] != '>'
		&& args[0][0] != '<')
	{
		pid = fork();
		if (pid == 0)
		{
			if (call_builtins(shell, 1, 0, 0) == 7)
			{
				execve(get_cmd(arg), ft_split(args[0], ' '), shell->env);
				perror("env");
				exit(127);
			}
			exit (0);
		}
		else
			waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else
		while (shell->env[++i])
			printf("%s\n", shell->env[i]);
	return (0);
}

char	*ft_str_eg_cpy(char *env, char *str)
{
	int		x;
	int		y;
	int		z;
	char	*tmp;
	int		mem;

	x = -1;
	y = -1;
	z = 0;
	while (env[++x] != '=')
		;
	tmp = malloc (((ft_strlen(str) - (ft_strlen(env) - (ft_strlen(env + x))) + ft_strlen(env + x))) * sizeof(char));
	x++;
	while (str[++y] != '$')
	{
		if (str[y] != 34 && str[y] != 39)
		{
			tmp[z] = str[y];
			z++;
		}
	}
	mem = y;
	while (env[x] != '\0')
	{
		tmp[z] = env[x];
		z++;
		x++;
	}
	while (str[mem] && (str[mem] != 32 && str[mem] != 9))
		mem++;
	while (str[mem] && str[mem] != 124)
	{
		tmp[z] = str[mem];
		mem++;
		z++;
	}
	tmp[z] = '\0';
	free(str);
	return (tmp);
}

char	*ft_str_without_exp(char *str, int exp)
{
	int	tmp;
	int	x;
	int	y;
	char	*str2;

	x = -1;
	while (str[++x] && str[x] != 32 && str[x] != 9)
		;
	tmp = exp;
	while (str[exp] && str[exp] >= 65 && str[exp] <= 90)
		--exp;
	str2 = malloc ((x + (tmp - exp) + 1) * sizeof(char));
	exp++;
	tmp++;
	x = -1;
	y = -1;
	while (++x <= tmp+1)
	{
		if (str[x] != '$' && str[x] != 34 && str[x] != 39)
			str2[++y] = str[x];
		if (str[x] == '$')
		{
			while (str[x] != 32 && str[x] != 9 && str[x] != 34 && str[x] != 39)
				++x;
		}
	}
	str2[++y] = '\0';
	return (str2);
}

char	*ft_ryoiki_tenkai(t_shell *shell, char *str, int exp)
{
	int	x;
	char *tmp;

	x = exp + 1;
	while (str[++x] && str[x] != 32 && str[x] != 39 && str[x] != 9 && str[x] != 124)
		;
	tmp = malloc (((x - exp) + 1) * sizeof(char));
	x = -1;
	while (str[++x] && str[x] != 32 && str[x] != 34 && str[x] != 9 && str[x] != 39)
	{
		tmp[x] = str[exp];
		exp++;
	}
	tmp[x] = '\0';
	printf("%s\n", tmp);
	x = -1;
	while (shell->env[++x])
	{
		if (ft_envstrcmp(tmp, shell->env[x]) == 0)
		{
			str = ft_str_eg_cpy(shell->env[x], str);
			return (str);
		}
	}
	str = ft_str_without_exp(str, exp);
	return (str);
}

int	ft_echo(t_shell *shell, char *arg)
{
	int		x;
	int		n;
	char	**tab;

	x = -1;
	n = 0;
	(void)shell;
	tab = ft_split(arg, ' ');
	while (tab[++x])
	{
		if (tab[x + 1])
			printf("%s ", tab[x]);
		else
			printf("%s", tab[x]);
	}
	if (n != 1)
		printf("\n");
	power_free(tab);
	return (0);
}
