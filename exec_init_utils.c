/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:34:43 by kgale             #+#    #+#             */
/*   Updated: 2021/09/14 19:15:02 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*get_writing_pipes(t_exec *exec)
{
	int	*indexes;
	int	i;
	int	count;

	count = 0;
	if (!exec->pipe_cnt)
		return (NULL);
	indexes = malloc(sizeof(int) * (exec->pipe_cnt + 1));
	while (count < exec->pipe_cnt)
	{
		i = exec->pipe_start[count];
		while (42)
		{
			i--;
			if (!i || !ft_strcmp(exec->words[i - 1], "\n|\n")
				|| !ft_strcmp(exec->words[i - 1], "\n;\n"))
				break ;
		}
		indexes[count] = i;
		count++;
	}
	indexes[count] = -1;
	return (indexes);
}

static int	*get_pipe_start(t_exec *exec)
{
	int	*pipe_start;
	int	i;
	int	count;

	i = 0;
	count = 0;
	pipe_start = NULL;
	if (!exec->pipe_cnt)
		return (NULL);
	pipe_start = malloc(sizeof(int) * (1 + exec->pipe_cnt));
	while (exec->words[i])
	{
		if (!ft_strcmp(exec->words[i], "\n|\n"))
			pipe_start[count++] = i;
		i++;
	}
	pipe_start[count] = -1;
	return (pipe_start);
}

void	exec_init_utils(t_exec *exec)
{
	exec->pipe_start = get_pipe_start(exec);
	exec->writing_from_pipes = get_writing_pipes(exec);
	if (exec->pipe_cnt > 0)
		exec->pipes_fds = malloc(sizeof(int *) * (1 + exec->pipe_cnt));
	exec->i = 0;
	while (exec->i < exec->pipe_cnt)
	{
		exec->pipes_fds[exec->i] = malloc(sizeof(int) * 2);
		pipe(exec->pipes_fds[exec->i]);
		exec->i++;
	}
	exec->i = 0;
}
