/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:49:34 by user42            #+#    #+#             */
/*   Updated: 2023/07/19 10:09:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int     check_arg(char *arg)
{
    int i;
    int equal;

    i = 0;
    equal = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            equal++;
        i++;
    }
    if (equal != 1)
        return (0);
    return (1);
}

int     check_exist(char *arg, t_shell *shell)
{
    int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_envstrcmp(shell->env[i], arg))
			return (1);
		i++;
	}
    return (0);
}

void    add_env(char *arg, t_shell *shell)
{
    char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		perror("malloc");
		return ;
	}
	memcpy(new_env, shell->env, i * sizeof(char *));
	new_env[i] = arg;
	new_env[i + 1] = NULL;
	shell->env = new_env;
    return ;
}

void    update_env(char *arg, t_shell *shell)
{
    int	i;

	i = 0;
	while (ft_envstrcmp(arg, shell->env[i]))
		i++;
	shell->env[i] = arg;
    return ;
}

void	ft_export(t_shell *shell, char *arg)
{
    char    **args;
    int     i;

    args = ft_split(arg, ' ');
	i = 0;
	while (args[i])
    {
        if(check_arg(args[i]))
        {
            if (!check_exist(args[i], shell))
                add_env(args[i], shell);
            else
                update_env(args[i], shell);
        }
        i++;
    }
    free(args);
	return ;
}