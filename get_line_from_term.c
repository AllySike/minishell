/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_term.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:08 by kgale             #+#    #+#             */
/*   Updated: 2021/09/12 01:42:48 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init(char **buff, int *i, char **res)
{
	*res = NULL;
	*buff = (char *)malloc(4000);
	ft_bzero(*buff, 4000);
	*i = 1;
}

static int read_buff(char **res, char **buff, char **str)
{
	int	n;

	ioctl(0, FIONREAD, &n);
	if (!*res)
	{
		*res = ft_strdup(*buff);
		if (n == 0)
		{
			free(*str);
			*str = ft_strdup(*res);
			free(*buff);
			free(*res);
			return (42);
		}
		ft_bzero(buff, 4000);
	}
	return (n);
}

static void	join_line(char **res, char **buff)
{
	int		length;
	char	*tmp;

	tmp = *res;
	*res = ft_strjoin(*res, *buff);
	length = ft_strlen(tmp) + ft_strlen(*buff);
	free(tmp);
	ft_bzero(*buff, 4000);
	ft_bzero(res + length, 1);
}

static void	clear_all(char **str, char **res, char **buff)
{
	if (*str)
		free(*str);
	*str = ft_strdup(*res);
	if (*buff)
		free(*buff);
	if (*res)
		free(*res);
}

int		get_line(char **str)
{
	int		n;
	int		i;
	char	*buff;
	char	*res;
	int		bytes;

	init(&buff, &i, &res);
	bytes = read(1, buff, 4000 - 1);
	while (bytes)
	{
		n = read_buff(&res, &buff, str);
		if (n == 42)
			return (bytes);
		i++;
		join_line(&res, &buff);
		if (n == 0)
			break ;
		bytes = read(1, buff, 4000 - 1);
	}
	clear_all(str, &res, &buff);
	return ((i - 1) * (4000 - 1) + bytes);
}
