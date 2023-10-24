/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_eg_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:47:58 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 19:04:34 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_eg_cpy_2(char *str, char *tmp, char *env, int x)
{
	int		y;
	int		z;

	z = 0;
	y = -1;
	while (str[++y] != '$')
	{
		if (str[y] != 34 && str[y] != 39)
		{
			tmp[z] = str[y];
			z++;
		}
	}
	while (env[x] != '\0')
	{
		tmp[z] = env[x];
		z++;
		x++;
	}
	if (str[ft_strlen(str) - 1] == 93 || (str[ft_strlen(str) - 2] == 93 && (str[ft_strlen(str) - 1] == 34)))
		tmp[z] = 93;
	return (tmp);
}

char	*ft_str_eg_cpy(char *env, char *str)
{
	int		x;
	char	*tmp;

	x = -1;
	while (env[++x] != '=')
		;
	tmp = ft_calloc(((ft_strlen(str) - (ft_strlen(env) - ((ft_strlen(env + x)))-1) + ft_strlen(env + x))), sizeof(char));
	x++;
	tmp = ft_str_eg_cpy_2(str, tmp, env, x);
	return (tmp);
}
