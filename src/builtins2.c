/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 18:47:48 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_without_exp_2(char *str, char *str2)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	if (ft_strncmp(str, "$", 2) == 0)
	{
		str2[0] = '$';
		str2[1] = '\0';
		return (str2);
	}
	while (str[++x])
	{
		if (str[x] && str[x] != '$' && str[x] != 34 && str[x] != 39)
			str2[++y] = str[x];
		if (str[x] == '$')
		{
			while (str[x] && str[x] != 32
				&& str[x] != 9 && str[x] != 34 && str[x] != 39)
				++x;
		}
	}
	str2[++y] = '\0';
	return (str2);
}

char	*ft_str_without_exp(char *str, int exp)
{
	int		tmp;
	int		x;
	char	*str2;

	x = -1;
	while (str[++x] && str[x] != 32 && str[x] != 9)
		;
	tmp = exp;
	while (str[exp] && str[exp] >= 65 && str[exp] <= 90)
		--exp;
	str2 = malloc ((x + (tmp - exp) + 1) * sizeof(char));
	tmp++;
	str2 = ft_str_without_exp_2(str, str2);
	return (str2);
}

char	*ft_extension_of_the_territory_2(t_shell *s, char *st,
	char *tmp, int exp)
{
	int	x;

	x = -1;
	while (s->env[++x])
	{
		if (ft_strlen(tmp) && ft_envstrcmp(tmp, s->env[x]) == 0)
		{
			st = ft_str_eg_cpy(s->env[x], st);
			printf("%s\n", st);
			return (st);
		}
	}
	st = ft_str_without_exp(st, exp);
	return (st);
}

char	*ft_extension_of_the_territory(t_shell *shell, char *str, int exp)
{
	int		x;
	int		y;
	char	*tmp;
	int		n;

	n = 0;
	x = -1;
	y = -1;
	if (str[0] == 39 || str[0] == 34)
	{
		tmp = malloc ((ft_strlen(str) - 1) * sizeof (char));
		++x;
	}
	else if (str[0] == 91 && str[1] == 36 && str[ft_strlen(str)] == 93)
		tmp = malloc ((ft_strlen(str) - 3));
	else
		tmp = malloc (ft_strlen(str));
	while (str[++x] && str[x] != 34 && str[x] != 39)
	{
		if (str[x] != 39 && str[x] != 34 && str[x] != 36 && str[x] != 91 && str[x] != 93 && str[x] != 92)
			tmp[++y] = str[x];
	}
	tmp[++y] = '\0';
	str = ft_extension_of_the_territory_2(shell, str, tmp, exp);
	free(tmp);
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
		return (0);
	tab = ft_split(arg, ' ');
	if (ft_strncmp(tab[0], "-n", 3) == 0 && !tab[1])
		return (0);
	if (ft_strncmp(tab[0], "-n", 3) == 0)
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
