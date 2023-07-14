/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:11:17 by user42            #+#    #+#             */
/*   Updated: 2023/07/13 23:04:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *check_path(char *path)
{
    int i;
    char    *new_path;

    if ((path[0] == '.' && path[1] == '/') || (path[0] == '~' && path[1] == '/') || path[0] == '/')
        return (path);
    i = -1;
    new_path = malloc(sizeof(char) * ft_strlen(path) + 3);
    if (!new_path)
    {
        perror("malloc");
        exit (0);
    }
    new_path[0] = '.';
    new_path[1] = '/';
    while (path[++i])
        new_path[i + 2] = path[i];
    new_path[i + 2] = '\0';
    return (new_path);
}

void    ft_cd(char *path)
{
    if (!path)
    {
        printf("Found no arg, default path is \"~/\"\n");
        chdir("~/");
    }
    else
    {
        printf("Path found;\n");
        path = check_path(path);
        chdir(path);
    }
}

void    ft_echo(char *arg)
{
    (void)arg;
    return ;
}

void    ft_pwd(char *arg)
{
    (void)arg;
    return ;
}

void    ft_export(char *arg)
{
    (void)arg;
    return ;
}

void    ft_unset(char *arg)
{
    (void)arg;
    return ;
}

void    ft_env(char *arg)
{
    (void)arg;
    return ;
}

void    ft_exit(char *arg)
{
    (void)arg;
    exit(0);
}