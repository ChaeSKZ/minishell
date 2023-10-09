/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:19 by jquil             #+#    #+#             */
/*   Updated: 2023/10/09 16:23:39 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_struct(t_shell *sh)
{
	sh->builtins = NULL;
	sh->line = NULL;
	sh->tokens = NULL;
	sh->env = NULL;
	sh->tab = NULL;
	sh->meta = NULL;
	sh->pid = 0;
	sh->errno = 0;
}
