/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:41:49 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/18 11:41:51 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_shell
{
	char	**builtins;
	void	(*f_ptr[7])(char *);
}		t_shell;

//-------- Utils --------

int		mnsh_strcmp(char *s1, char *s2);
char	*get_args(char *line);
char	*get_cmd(char *line);
char	*get_cmd_name(char *line);

//------- Builtins ------

void	ft_echo(char *arg);
void	ft_cd(char *cmd_line);
void	ft_pwd(char *arg);
void	ft_export(char *arg);
void	ft_unset(char *arg);
void	ft_env(char *arg);
void	ft_exit(char *arg);

#endif
