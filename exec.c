/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:14:01 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:31:55 by kgale            ###   ########.fr       */
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
	if (exec->wr_redir)
		free(exec->wr_redir);
	if (exec->redir_read)
		free(exec->redir_read);
	free_array(&exec->func_args);
	exec->i++;
}

int	ft_exit(char **array)
{
	int				i;
	unsigned char	res;
	int				mltpl_args_flag;

	mltpl_args_flag = 0;
	res = 0;
	i = 0;
	if (array[1] == NULL)
		return (127);
	if (array[2])
		mltpl_args_flag = 1;
	while (array[1][i])
	{
		if (!ft_isdigit(array[1][i]))
		{
			ft_putstr_fd(" exit: numeric argument required\n", 2);
			return (255);
		}
		res = res * 10 + (array[1][i] - '0');
		i++;
	}
	if (mltpl_args_flag)
	{
		ft_putstr_fd(" exit: too many arguments\n", 2);
		return (-1);
	}
	return (res);
}

static void	ft_exit1(t_exec *exec, t_all *all)
{
	exec->ret = ft_exit(exec->func_args);
	if (exec->ret == -1)
	{
		all->ret = 1;
		return ;
	}
	else
		exit(exec->ret);
}

void	exec(t_all *all)
{
	t_exec exec;

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
			ft_exit1(&exec, all);
			return ;
		}
		else
			pid_create(&exec, &(all->envp));
		wait(&exec.wstatus);
		exec_wait(&exec);
	}
	exec_free(&exec);
}
