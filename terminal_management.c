/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:15 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:04:48 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_setup(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
	write(1, "minishell$ ", 12);
	tputs(save_cursor, 1, ft_putchar);
}

static t_list	*press_up_down_helper(t_all *all, int flag, int *cnt)
{
	t_list	*hist;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	hist = all->history;
	if (flag)
	{
		if (*cnt == -1)
			ft_bzero(all->command, ft_strlen(all->command));
		if (*cnt < all->max_indx - 1)
			(*cnt)++;
	}
	else if (*cnt > 0)
		(*cnt)--;
	return (hist);
}

static void	press_up_down(t_all *all, int flag, int *cnt)
{
	int		slider;
	t_list	*hist;
	char	*tmp;

	slider = 0;
	hist = press_up_down_helper(all, flag, cnt);
	while (hist)
	{
		if (slider == *cnt)
		{
			ft_putstr_fd((hist)->content, 1);
			ft_bzero(all->command, ft_strlen(all->command));
			tmp = all->command;
			all->command = ft_strjoin(all->command, (hist)->content);
			free(tmp);
			all->line_len = ft_strlen((hist)->content);
			break ;
		}
		slider++;
		hist = (hist)->next;
	}
}

static void	append_command(t_all *all)
{
	char	*tmp;

	all->line_len += all->read_bytes;
	tmp = all->command;
	all->command = ft_strjoin(all->command, all->line);
	free(tmp);
}

void	input_management(t_all *all, int *cnt)
{
	while (42)
	{
		input_helper(all);
		if (!ft_strcmp(all->line, cursor_up))
			press_up_down(all, 1, cnt);
		else if (!ft_strcmp(all->line, "\e[B"))
			press_up_down(all, 0, cnt);
		else if (!ft_strcmp(all->line, "\177") && all->line_len)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			ft_bzero(all->command + (ft_strlen(all->command) - 1), 1);
			all->line_len--;
		}
		else if (all->line[0] >= 0 && all->line[0] <= 126)
		{
			write(1, all->line, all->read_bytes);
			if (!ft_strcmp(all->line, "\n")
				|| (!ft_strcmp(all->line, "\004")
					&& !ft_strlen(all->command)))
				break ;
			if (all->line[0] >= 32 && all->line[0] <= 126)
				append_command(all);
		}
	}
}
