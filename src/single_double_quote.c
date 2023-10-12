/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:20 by jquil             #+#    #+#             */
/*   Updated: 2023/10/12 19:27:28 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_not_quoted(char *str, int end)
{
	int	x;
	int	p1;
	int	p2;

	x = -1;
	while (str[++x])
	{
		if (str[x] == 39)
		{
			p1 = x;
			while (str[++x] != 39)
				;
			p2 = x;
			if (end > p1 && end < p2)
				return (0);
		}
		if (str[x] == 34)
		{
			p1 = x;
			while (str[++x] != 34)
				;
			p2 = x;
			if (end > p1 && end < p2)
				return (0);
		}
	}
	return (1);
}

int	expand_not_quoted(char *str, int dollar)
{
	int	x;
	int	p1;
	int	p2;

	x = -1;
	while (str[++x])
	{
		if (str[x] == 39)
		{
			p1 = x;
			while (str[++x] != 39)
				;
			p2 = x;
			if (dollar > p1 && dollar < p2)
				return (0);
		}
	}
	return (1);
}

int	ft_find_end(char *str, int start)
{
	int	end;

	end = start + 1;
	while (str[end])
	{
		if (str[end] == 124 && pipe_not_quoted(str, end) == 1)
			return (end);
		end++;
	}
	return (end);
}

int	ft_need_expand(char *str)
{
	int x;

	x = -1;
	while (str[++x])
		if (str[x] == '$')
			return (x);
	return (-1);
}

char	*ft_add_str(t_shell *shell, char *str, int start, int end)
{
	char	*dest;
	int		x;

	x = 0;
	dest = malloc ((end - start + 1) * sizeof(char));
	(void)shell;
	while (start < end)
	{
		if (str[start] != 34 && str[start] != 39)
		{
			dest[x] = str[start];
			x++;
		}
		start++;
	}
	dest[x] = '\0';
	return (dest);
}

int	calc_size(char **tab, int idx, int size)
{
	int	n_size;

	n_size = 0;
	while (size)
	{
		n_size += ft_strlen(tab[idx - size]) + 1;
		size--;
	}
	n_size += ft_strlen(tab[idx - size]);
	return (n_size);
}

char	*copy_line(char **tab, int idx, int size)
{
	char	*new;

	new = calloc(sizeof(char) * (calc_size(tab, idx, size) + 1), 0);
	if (!new)
		return (perror("malloc"), NULL);
	while (size)
	{
		new = str_add(new, tab[idx - size], 0);
		new = str_add(new, " ", 0);
		size--;
	}
	new = str_add(new, tab[idx], 0);
	return (new);
}

char	**resplit_tab(char **tab)
{
	char **new;
	int		i;
	int		n;
	int		size;

	i = -1;
	size = 1;
	n = 0;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "|", 1) == 0)
			size++;
	}
	new = calloc(sizeof(char *) * (size + 1),  0);
	if (!new)
		return (perror("malloc"), NULL);
	i = -1;
	size = 0;
	while (tab[++i])
	{
		if (tab[i + 1] == NULL || ft_strncmp(tab[i + 1], "|", 1) == 0)
		{
			if (n > 0)
				size--;
			new[n] = copy_line(tab, i, size);
			n++;
			size = -1;
		}
		size++;
	}
	new[n] = NULL;
	//power_free(tab);
	return (new);
}

// {
// 	int	nb;
// 	int	x;
// 	int	i;
// 	char **res;
// 	int	z;

// 	x = -1;
// 	i = -1;
// 	nb = 1;
// 	z = 0;
// 	while (tab[++i])
// 	{
// 		while (tab[i][++x])
// 			if(tab[i][x] == 124)
// 				nb++;
// 		x = -1;
// 	}
// 	res = malloc (nb * sizeof(char *));
// 	i = 0;
// 	x = -1;
// 	nb = -1;
// 	print_tab(tab);
// 	while (tab[i])
// 	{
// 		while (tab[i] && tab[i][0] != 124)
// 			i++;
// 		printf("i = %i\n", i);
// 		while (++x < i)
// 			nb += ft_strlen(tab[x]);
// 		res[z] = malloc ((nb + 2) * sizeof (char));
// 		nb = 0;
// 		x = 0;
// 		while (nb < i)
// 		{
// 			res[z] = add_str_stat(tab[nb]);
// 			nb++;
// 		}
// 		z++;
// 		i++;
// 	}
// 	power_free(tab);
// 	return (res);
// }

char	**ft_split_str(t_shell *shell, char *str, char **tab)
{
	int		z;

	z = -1;
	(void)shell;
	tab = ft_split(str, ' ');
	while (tab[++z])
	{
		if (ft_need_expand(tab[z]) != -1 && expand_not_quoted(tab[z], ft_need_expand(tab[z]) == 1))
			tab[z] = ft_ryoiki_tenkai(shell, tab[z], ft_need_expand(tab[z]) + 1);
	}
	tab = resplit_tab(tab);
	return (tab);
}

bool	ft_next_quote(char *arg, int type, int x)
{
	int	y;

	y = x;
	while (arg[++y])
	{
		if (arg[y] == type)
			return (1);
	}
	return (0);
}

char	**ft_split_quote(t_shell *shell, char *arg)
{
	int		x;
	char	**tab;

	tab = NULL;
	x = -1;
	while (arg[++x])
	{
		if (arg[x] == 39 && ft_next_quote(arg, 39, x) == 1)
		{
			while (arg[++x] && arg[x] != 39)
				;
		}
		else if (arg[x] == 34 && ft_next_quote(arg, 34, x) == 1)
		{
			while (arg[++x] && arg[x] != 34)
				;
		}
		else if ((arg[x] == 34 && ft_next_quote(arg, 34, x) == 0) || (arg[x] == 39 && ft_next_quote(arg, 39, x) == 0))
			return (NULL);
	}
	return (ft_split_str(shell, arg, tab));
}
