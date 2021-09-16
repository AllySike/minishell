/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:31 by kgale             #+#    #+#             */
/*   Updated: 2021/09/16 11:35:45 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_check;

static void	handle(int sig)
{
	if (sig == SIGINT && (g_check == 0 || g_check == 2))
	{
		write(1, "\nminishell$ ", 13);
		g_check = 2;
	}
	else if (sig == SIGQUIT && g_check == 1)
		write(1, "Quit: 3\n", 9);
}

static void	ft_init_all(t_all *all, char **envp)
{
	int		i;

	i = 0;
	all->envp = ft_lstnew(ft_strdup(envp[i]));
	while (envp[++i])
		ft_lstadd_back(&(all->envp), ft_lstnew(ft_strdup(envp[i])));
	signal(SIGINT, &handle);
	signal(SIGQUIT, &handle);
	all->ret = 0;
	all->line = ft_strdup("\0");
	all->command = ft_strdup("\0");
	all->max_indx = 0;
	all->history = ft_lstnew(ft_strdup("\0"));
	ft_lstadd_front(&(all->history), ft_lstnew(ft_strdup("\0")));
	all->max_indx++;
}

void	input_helper(t_all *all)
{
	all->read_bytes = get_line(&(all->line));
	(all->line)[all->read_bytes] = '\0';
	if (g_check == 2)
	{
		ft_bzero(all->command, ft_strlen(all->command));
		all->line_len = 0;
		g_check = 0;
	}
}

static void	launch(t_all *all)
{
	struct termios	term;
	int				cnt;

	tcgetattr(0, &term);
	while (ft_strcmp(all->line, "\004"))
	{
		terminal_setup();
		all->line_len = 0;
		input_management(all, &cnt);
		tcsetattr(0, TCSANOW, &term);
		g_check = 1;
		cnt = 0;
		if (all->command[0])
			exec(all);
		g_check = 0;
		if (ft_strcmp(all->command, "\0"))
		{
			free(all->history->content);
			all->history->content = ft_strdup(all->command);
			ft_lstadd_front(&(all->history), ft_lstnew(ft_strdup("\0")));
			all->max_indx++;
		}
		ft_bzero(all->command, ft_strlen(all->command));
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_all			all;

	(void)argv;
	if (argc > 1)
	{
		write(2, "Error:\nToo many args\n", 22);
		return (1);
	}
	ft_init_all(&all, envp);
	launch(&all);
	if (all.command)
		free(all.command);
	if (all.line)
		free(all.line);
	ft_lstclear(&(all.envp), free);
	ft_lstclear(&(all.history), free);
	return (0);
}
