/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:35:04 by kgale             #+#    #+#             */
/*   Updated: 2021/09/16 10:30:41 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **array)
{
	int		i;
	char	dir[50000];

	i = 0;
	while (array[i])
		i++;
	if (i > 1)
	{
		write(2, "pwd: too many arguments\n", 24);
		return ;
	}
	getcwd(dir, 50000);
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
}
