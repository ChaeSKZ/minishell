/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:41:49 by jugingas          #+#    #+#             */
/*   Updated: 2023/09/28 10:41:51 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <string.h>

# define RESET "\033[0m"
# define RED "\e[0;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[1;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"

# define MAX_PATH_SIZE 1024

typedef struct s_pp
{
	int	pid;
	int	*pidtab;
	int	cmd_nb;
	int	pipe_nb;
	// int	cmd1_pid;
	// int	cmd2_pid;
	int	*pipe;
	int	idx;
}		t_pp;


typedef struct s_shell
{
	char	**builtins;
	char	*line;
	char	**tokens;
	char	**env;
	int		*meta;
	char	*envp[1];
	char	ex_path[MAX_PATH_SIZE];
	int		pid;
	void	(*f_ptr[7])(struct s_shell *, char *);
}		t_shell;

//-------- Utils --------

char	**ft_split(char const *s, char c);
char	**token_it(t_shell *shell, char *str);
char	*ft_strdup(const char *s);
char	*ft_epurstr(char *str);
char	**epur_tab(char **tab);
int		ft_strncmp(char *s1, char *s2, int n);
void	power_free(char **tab);
int		mnsh_strcmp(char *s1, char *s2);
int		ft_envstrcmp(char *s1, char *s2);
char	*get_args(char *line);
char	*get_cmd(char *line);
char	*get_cmd_name(char *line);
int		ft_strlen(const char *str);
char	*ft_split_quote(t_shell *shell, char *arg);
void	init_signals(void);


//------ Redirects -----

char	*get_heredoc(char *delimiter);
int		simple_right(char *filename);
int		double_right(char *filename);
int		simple_left(char *filename);
int		double_left(char *cmd, char *delimiter, char **env);

//-------- Pipes -------

int		ft_pipe(t_shell *shell, char **token);
int		cmd_count(char **token);
void	create_pipes(t_pp *pp);
void	close_pipes(t_pp *pp);
void	dup2_spe(int z, int f);

//------- Builtins ------

void	ft_echo(t_shell *shell, char *arg);
void	ft_cd(t_shell *shell, char *cmd_line);
void	ft_pwd(t_shell *shell, char *arg);
void	ft_export(t_shell *shell, char *arg);
void	ft_unset(t_shell *shell, char *arg);
void	ft_env(t_shell *shell, char *arg);
void	ft_exit(t_shell *shell, char *arg);

//-------- env ----------

void	init_env(t_shell *shell, char **env);
void	create_env(t_shell *shell);
char	*get_home_path(char **env);
void	update_env(char *arg, t_shell *shell);

#endif
