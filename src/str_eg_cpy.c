/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_eg_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:47:58 by jquil             #+#    #+#             */
/*   Updated: 2023/10/13 18:59:09 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_eg_cpy_3(char *str, char *tmp, int mem, int z)
{
	(void)z;
	(void)mem;
	// printf("str : %s\ntmp : %s\n", str, tmp);
	// while (str[mem] && (str[mem] != 32 && str[mem] != 9))
	// 	mem++;
	// while (str[mem] && str[mem] != 124)
	// {
	// 	tmp[z] = str[mem];
	// 	mem++;
	// 	z++;
	// }
	// // if (str[0] == 91 && str[mem - 1] == 93)
	// // {
	// // 	tmp[z] = 93;
	// // 	++z;
	// // }
	// tmp[z] = '\0';
	free(str);
	return (tmp);
}

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
	if (str[ft_strlen(str)-2] == 93)
		tmp[z] = 93;
	printf("%s\n", tmp);
	tmp = ft_str_eg_cpy_3(str, tmp, y, z);
	printf("%s\n", tmp);
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
