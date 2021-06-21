/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:32:34 by kgale             #+#    #+#             */
/*   Updated: 2021/06/21 17:32:34 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
static int	g_check;

// void	sigint(int signo)
// {
// 	if (g_check == 0 || g_check == 2)
// 	{
// 		readline(PROMPT);
// 		g_check = 2;
// 	}
// }

// void	handle_quit(int signo)
// {
// 	if (g_check == 1)
// 	{
// 		write(1, "Quit: ", 6);
// 		ft_putnbr_fd(signo, 1);
// 		write(1, "\n", 1);
// 	}
// }

int main(int args, char *argv[], char *envp[])
{
	char	*line;
	int		gnl;
	// struct termios	termios_p;

	// signal(SIGINT, &sigint);
	// signal(SIGQUIT, &handle_quit);
	while (1)
	{
		line = readline(PROMPT);
		printf("%s\n", line);
		if (line && *line)
			add_history(line);

		line_parser(line, envp);
		free(line);
	}
	return (0);
}
