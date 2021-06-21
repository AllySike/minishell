/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:31:25 by kgale             #+#    #+#             */
/*   Updated: 2021/06/21 18:38:05 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	line_parser(char *line, char *envp[])
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "exit", 4) == 0)
		exit (0);
	if (ft_strncmp(line, "env", 3) == 0)
		while (*envp)
			printf("%s\n", *envp++);
}
