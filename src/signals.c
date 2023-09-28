/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:22:51 by jquil             #+#    #+#             */
/*   Updated: 2023/09/28 11:56:59 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_signals(int sig)
{
	if (sig == 2)
	{
		printf("\n$>");
		return (2);
	}
	else
		printf("%i\n", sig);
	return (0);
}

void	init_signals(void)
{
	struct sigaction	sb;

	sb.sa_handler = (void *)ft_signals;
	sigemptyset(&sb.sa_mask);
	sb.sa_flags = 0;
	sigaction(SIGINT, &sb, 0);
	signal(SIGQUIT, SIG_IGN);
}
