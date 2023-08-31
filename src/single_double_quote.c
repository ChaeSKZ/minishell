/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_&_double_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/08/31 11:01:37 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		else if (arg[x] == 34)
			++nb;
	}
	if (nb == 2)
		shell->meta = 0;
	// si nb != 2 -> quote = char
}
