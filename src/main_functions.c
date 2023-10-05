/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:18:08 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/05 12:21:42 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_shell *shell)
{
	if (!shell->errno)
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" GREEN "OK" RESET "] " BLUE "$> " RESET);
	else
		shell->line = readline(GREEN "→ " CYAN "minishell" RESET
				" [" RED "KO" RESET "] " BLUE "$> " RESET);
}
