/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 11:17:56 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = ft_calloc(((ft_strlen(str) - (ft_strlen(env)
						- (ft_strlen(env + x)))
					+ ft_strlen(env + x))), sizeof(char));
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
	int		tmp;
	int		x;
	int		y;
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
	while (++x <= tmp + 1)
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
	int		x;
	int		y;
	char	*tmp;
	int		n;

	n = 0;
	x = -1;
	y = -1;
	if (str[0] == 39 || str[0] == 34 || str[0] == 36)
	{
		tmp = malloc ((ft_strlen(str) - 1) * sizeof (char));
		++x;
	}
	while (str[++x] && str[x] != 34 && str[x] != 39)
	{
		if (str[x] != 39 && str[x] != 34 && str[x] != 36)
			tmp[++y] = str[x];
	}
	tmp[++y] = '\0';
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
	(void)shell;
	if (!arg || ft_strncmp(arg, "", 1) == 0)
		return (printf("\n"), 0);
	tab = ft_split(arg, ' ');
	if (ft_strncmp(tab[0], "-n", 2) == 0)
		n = ++x + 1;
	else
		n = 0;
	while (tab[++x + 1])
		printf("%s ", tab[x]);
	printf("%s", tab[x]);
	if (n != 1)
		printf("\n");
	power_free(tab);
	return (0);
}
