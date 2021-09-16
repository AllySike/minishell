/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:32:02 by kgale             #+#    #+#             */
/*   Updated: 2021/09/16 10:42:21 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_utils(char **array)
{
	int		i;
	char	*tmp;

	i = 1;
	while (array[i])
	{
		tmp = ft_strdup(array[i]);
		ft_putstr_fd(tmp, 1);
		free(tmp);
		i++;
		if (array[i] != NULL)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	ft_echo(char **array)
{
	char	*tmp;
	int		i;

	if (!array[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(ft_strdup(array[1]), "-n") == 0)
	{
		if (!array[2])
			return ;
		i = 2;
		while (array[i])
		{
			tmp = ft_strdup(array[i]);
			write(1, tmp, ft_strlen(array[i]));
			free(tmp);
			i++;
			if (array[i])
				write(1, " ", 1);
		}
	}
	else
		ft_echo_utils(array);
}
