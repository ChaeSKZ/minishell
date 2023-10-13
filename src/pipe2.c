/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:01:09 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/13 11:27:59 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_count(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

void	create_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < pp->cmd_nb - 1)
	{
		pipe(pp->pipe + 2 * i);
		i++;
	}
}

void	close_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < pp->pipe_nb)
	{
		close(pp->pipe[i]);
		i++;
	}
}

void	dup2_spe(int z, int f)
{
	dup2(z, 0);
	dup2(f, 1);
}

void	do_the_redirections(t_pp *pp)
{
	if (pp->idx == 0)
		dup2_spe(STDIN_FILENO, pp->pipe[1]);
	else if (pp->idx < pp->cmd_nb - 1)
		dup2_spe(pp->pipe[2 * pp->idx - 2], pp->pipe[2 * pp->idx + 1]);
	else
		dup2_spe(pp->pipe[2 * pp->idx - 2], STDOUT_FILENO);
	close_pipes(pp);
}
