/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:41:49 by jugingas          #+#    #+#             */
/*   Updated: 2023/07/18 14:12:26 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX_PATH_SIZE 1024

typedef struct s_shell
{
	char	**builtins;
	char	*line;
	char	**env;
	char	*envp[1];
	int		pid;
	void	(*f_ptr[7])(struct s_shell *, char *);
}		t_shell;

//-------- Utils --------

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
void	power_free(char **tab);
int		mnsh_strcmp(char *s1, char *s2);
int		ft_envstrcmp(char *s1, char *s2);
char	*get_args(char *line);
char	*get_cmd(char *line);
char	*get_cmd_name(char *line);

//------- Builtins ------

void	ft_echo(t_shell *shell, char *arg);
void	ft_cd(t_shell *shell, char *cmd_line);
void	ft_pwd(t_shell *shell, char *arg);
void	ft_export(t_shell *shell, char *arg);
void	ft_unset(t_shell *shell, char *arg);
void	ft_env(t_shell *shell, char *arg);
void	ft_exit(t_shell *shell, char *arg);

#endif
