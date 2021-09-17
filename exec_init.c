/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:28:38 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:28:38 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_syntax_errors(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if ((!ft_strcmp("\n|\n", words[i])
				|| !ft_strcmp("\n;\n", words[i])
				|| !ft_strcmp("\n>\n", words[i])
				|| !ft_strcmp("\n<\n", words[i])
				|| !ft_strcmp("\n>>\n", words[i]))
			&& (!words[i + 1] || !i
				|| (!ft_strcmp("\n|\n", words[i + 1])
					|| !ft_strcmp("\n;\n", words[i + 1])
					|| !ft_strcmp("\n<\n", words[i + 1])
					|| !ft_strcmp("\n>\n", words[i + 1])
					|| !ft_strcmp("\n>>\n", words[i + 1]))))
		{
			write(2, "Syntax error near token: ", 26);
			ft_putstr_fd(words[i] + 1, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	functions_count(char **argv)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	while (argv[i])
	{
		if ((!ft_strcmp(argv[i], "\n|\n")
				|| !ft_strcmp(argv[i], "\n;\n"))
			&& argv[i + 1] && *argv[i + 1])
		{
			nbr++;
		}
		if ((!i || !ft_strcmp(argv[i - 1], "\n|\n")
				|| !ft_strcmp(argv[i - 1], "\n;\n"))
			&& (!ft_strcmp(argv[i], "\n>\n")
				|| !ft_strcmp(argv[i], "\n<\n")))
			nbr--;
		i++;
	}
	return (nbr);
}

static void	check_fd(int i, char *argv)
{
	int	fd;

	fd = i;
	fd = open(argv, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd(argv, 2);
		write(2, ": No such file or directory\n", 29);
	}
	else
		close(fd);
}

static int	*get_func_start(t_exec *exec)
{
	int	i;
	int	count;
	int	*res;

	i = 0;
	count = 0;
	res = malloc(sizeof(int) * (exec->func_cnt + 1));
	while (exec->words[i])
	{
		if (!i || !ft_strcmp(exec->words[i - 1], "\n;\n")
			|| !ft_strcmp(exec->words[i - 1], "\n|\n"))
		{
			if (!ft_strcmp(exec->words[i], "\n<\n"))
				check_fd(i, exec->words[i + 1]);
			else
				res[count++] = i;
		}
		i++;
	}
	res[count] = '\0';
	return (res);
}

int	exec_init(t_exec *exec, t_all *all)
{
	int	i;

	exec->pipes_fds = NULL;
	exec->words = process_inputs(all->command, all->envp, all->ret);
	if (!exec->words || !process_syntax_errors(exec->words))
		return (0);
	exec->func_cnt = functions_count(exec->words);
	exec->func_start = get_func_start(exec);
	exec->pipe_cnt = 0;
	i = 0;
	while (exec->words[i++])
		if (!ft_strcmp(exec->words[i - 1], "\n|\n"))
			exec->pipe_cnt++;
	exec_init_utils(exec);
	return (1);
}
