/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:32:20 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:31:27 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_utils(char **env, char **array, char *path)
{
	int		i;
	char	*tmp_1;
	char	*tmp_2;
	char	**paths;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp_1 = ft_strjoin(paths[i], "/\0");
		tmp_2 = ft_strjoin(tmp_1, array[0]);
		free(tmp_1);
		execve(tmp_2, array, env);
		free(tmp_2);
		i++;
	}
	free_array(&paths);
}

static void	ft_exec(char **env, char **array)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
		&& env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	ft_exec_utils(env, array, path);
	execve(array[0], array, env);
	write(2, "no such command: ", 17);
	ft_putstr_fd(array[0], 2);
	write(2, "\n", 1);
	free(path);
	exit(127);
}

static void	dup2_redir_handle(t_exec *exec)
{
	if (exec->wr_redir_case == 1)
	{
		exec->fd = open(exec->wr_redir, O_WRONLY | O_CREAT, 0777);
		dup2(exec->fd, 1);
		close(exec->fd);
	}
	if (exec->pipe_cnt)
	{
		exec->j = 0;
		while (exec->j < exec->pipe_cnt)
		{
			if (exec->func_start[exec->i] == exec->writing_from_pipes[exec->j]
				&& !exec->wr_redir_case)
				dup2(exec->pipes_fds[exec->j][1], 1);
			else if (exec->func_start[exec->i] == exec->pipe_start[exec->j] + 1
				&& !exec->r_redir_case)
				dup2(exec->pipes_fds[exec->j][0], 0);
			exec->j++;
		}
	}
}

static void	dup2_redir(t_exec *exec)
{
	if (exec->wr_redir_case == 2)
	{
		exec->fd = open(exec->wr_redir, O_WRONLY | O_APPEND | O_CREAT, 0777);
		dup2(exec->fd, 1);
		close(exec->fd);
	}
	else if (exec->r_redir_case == 1)
	{
		exec->fd = open(exec->redir_read, O_RDONLY, 0777);
		if (exec->fd == -1)
		{
			ft_putstr_fd(exec->redir_read, 2);
			write(2, ": No such file or directory\n", 29);
			exit(1);
		}
		dup2(exec->fd, 0);
		close(exec->fd);
	}
}

void	pid_create(t_exec *exec, t_list **list_envp)
{
	exec->pid = fork();
	exec->j = 0;
	while (exec->j < exec->pipe_cnt)
	{
		if (exec->func_start[exec->i] == exec->pipe_start[exec->j] + 1)
			close(exec->pipes_fds[exec->j][1]);
		exec->j++;
	}
	if (exec->pid == 0)
	{
		dup2_redir(exec);
		dup2_redir_handle(exec);
		if (!ft_strcmp(exec->func_args[0], "pwd"))
			ft_pwd(exec->func_args);
		else if (!ft_strcmp(exec->func_args[0], "export"))
			ft_declare(*list_envp, exec->func_args);
		else if (!ft_strcmp(exec->func_args[0], "echo"))
			ft_echo(exec->func_args);
		else if (!ft_strcmp(exec->func_args[0], "env"))
			ft_env(*list_envp);
		else if (ft_strcmp(exec->func_args[0], "cd"))
			ft_exec(ft_lstarr(*list_envp), exec->func_args);
		exit(0);
	}
}
