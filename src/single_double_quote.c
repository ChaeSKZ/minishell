/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/09/06 18:01:18 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_split_quote(t_shell *shell, char *arg)
{
	int	x;
	int	nb;

	x = -1;
	nb = 0;
	while (++x < ft_strlen(arg))
	{
		if (arg[x] == 39)
			++nb;
	}
	if (nb == 2)
		shell->meta = -1;
	x = -1;
	nb = 0;
	while (++x < ft_strlen(arg))
	{
		if (arg[x] == 34)
			++nb;
	}
	if (nb == 2)
		shell->meta = 0;
	return (NULL);
	// si nb != 2 -> quote = char
}
