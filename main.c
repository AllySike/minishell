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

//static int	g_check;

void	sigint(int signo)
{
//	if (g_check == 0 || g_check == 2)
	{
		write(1, "\n > ", 4);
//		g_check = 2;
	}
}

void	sigquit(int signo)
{
//	if (g_check == 1)
	{
		write(1, "Quit: ", 6);
		ft_putnbr_fd(signo, 1);
		write(1, "\n", 1);
	}
}

int main(int args, char *argv[], char *envp[])
{
	t_minishell	shell;
	int		gnl;
	struct termios	termios_p;

	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	shell.status = 0;
	tcgetattr(0, &termios_p);
	shell.envp = envp;
	shell.line = readline(PROMPT);
	 while (shell.line && *shell.line)
	 {
	 	line_parser(shell.line, envp);
	 	free(shell.line);
	 	shell.line = readline(PROMPT);
	 }
	return (0);
}
