/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:59:22 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/27 11:29:46 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell, char *arg)
{
	char	cwd[MAX_PATH_SIZE];

	(void)arg;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("cwd");
	return ;
}

void	ft_unset(t_shell *shell, char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		if (ft_envstrcmp(shell->env[i], arg) == 0)
		{
			j = i;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	ft_env(t_shell *shell, char *arg)
{
	int	i;

	i = -1;
	(void)arg;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return ;
}

void	ft_echo(t_shell *shell, char *arg)
{
	int		x;
	char	*arg2;

	(void)shell;
	x = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		arg2 = malloc ((ft_strlen(arg) - 2) * sizeof (char));
		while (++x < ft_strlen(arg))
			arg2[x - 3] = arg[x];
		arg2[x - 3] = '\0';
	}
	else
	{
		arg2 = malloc ((ft_strlen(arg)) * sizeof (char));
		arg2 = arg;
	}
	printf("oui\n");
	if (shell->meta[0] == 2 || shell->meta[0] == 1)
		printf("%s", arg2);
	else
	{
		x = -1;
		while (++x < ft_strlen(arg2))
		{
			if ((arg2[x] == 92 && arg2[x + 1] == 110) && ((x + 1) == ft_strlen(arg2) - 1))
			{
				arg2[x] = 'n';
				arg2[x + 1] = '\0';
			}
			if (arg2[x] == 92 && arg2[x + 1] == 110)
			{
				arg2[x] = 'n';
				x = x + 1;
			}
		}
		printf("%s", arg2);
	}
	free(arg2);
	return ;
}
/*
echo -n "test"
test			-> " a virer mais sinon OK

echo -n "test\n"
test\n			-> " a virer mais sinon OK nan enft desfois c'est ok desfois y'a dla merde

echo -n test\n
testn			->

echo -n test | cat -e
test

echo -n "test" | cat -e
test

echo -n "test\n" | cat -e
test\n

echo -n test\n | cat -e
testn
*/

/*
	bool    bs;

	(void)shell;
    bs = 1;
    if ((arg[0] == '-') && (arg[1] == 'n'))
        bs = 0;
    if (bs == 0)
        printf("%s", arg);
    else
        printf("%s\n", arg);
*/
