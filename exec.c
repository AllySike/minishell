/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:14:01 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 16:20:41 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_handle(t_all *all, t_exec *exec)
{
	exec->words = process_inputs(all->command, all->envp, all->ret);
	exec->wr_redir_case = redir_output(exec, exec->func_start[exec->i + 1] - 1);
	exec->r_redir_case = redir_input(exec, exec->func_start[exec->i + 1] - 1);
	if (exec->r_redir_case == -1)
		return (0);
	exec->func_args = get_fnct_args(exec,
			exec->func_start[exec->i + 1] - 1);
	return (1);
}

static void	exec_free(t_exec *exec)
{
	exec->i = 0;
	if (exec->pipe_cnt > 0)
	{
		while (exec->i < exec->pipe_cnt)
		{
			free(exec->pipes_fds[exec->i]);
			exec->i++;
		}
		free(exec->pipes_fds);
	}
	free_array(&exec->words);
	free(exec->func_start);
	if (exec->pipe_start)
		free(exec->pipe_start);
	if (exec->writing_from_pipes)
		free(exec->writing_from_pipes);
}

static void	exec_wait(t_exec *exec)
{
	wait(&exec->wstatus);
	if (exec->wr_redir)
		free(exec->wr_redir);
	if (exec->redir_read)
		free(exec->redir_read);
	free_array(&exec->func_args);
	exec->i++;
}

static void	ft_exit(t_exec *exec, t_all *all)
{
	int	i;

	exec->ret = 0;
	i = 0;
	if (!exec->func_args[1])
		exit(127);
	while (exec->func_args[1][i])
	{
		if (!ft_isdigit(exec->func_args[1][i]))
		{
			ft_putstr_fd(" exit: numeric argument required\n", 2);
			exit(255);
		}
		exec->ret = exec->ret * 10 + (exec->func_args[1][i] - '0');
		i++;
	}
	if (exec->func_args[2])
	{
		ft_putstr_fd(" exit: too many arguments\n", 2);
		all->ret = 1;
		exit(-1);
	}
	exit(exec->ret);
}

void	exec(t_all *all)
{
	t_exec	exec;

	if (!exec_init(&exec, all))
		return ;
	while (exec.i < exec.func_cnt)
	{
		free_array(&exec.words);
		if (!redir_handle(all, &exec))
			return ;
		if (!ft_strcmp(exec.func_args[0], "export"))
			ft_export(&(all->envp), exec.func_args);
		else if (!ft_strcmp(exec.func_args[0], "unset"))
			ft_unset(&(all->envp), exec.func_args);
		else if (!ft_strcmp(exec.func_args[0], "cd"))
			ft_chdir(exec.func_args, &(all->envp));
		else if (!ft_strcmp(exec.func_args[0], "exit"))
		{
			ft_exit(&exec, all);
			return ;
		}
		else
			pid_create(&exec, &(all->envp));
		exec_wait(&exec);
	}
	exec_free(&exec);
}
