/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:34:12 by kgale             #+#    #+#             */
/*   Updated: 2021/09/15 15:34:57 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_output_utils(char **dir)
{
	int fd;

	fd = open(*dir, O_WRONLY | O_APPEND | O_CREAT, 0777);
	close(fd);
	free(*dir);
	*dir = NULL;
}

int		redir_output(t_exec *exec, int finish)
{
	int i;
	int nbr;

	i = exec->func_start[exec->i];
	nbr = 0;
	exec->wr_redir = NULL;
	while (i < finish || (finish == -1 && exec->words[i]))
	{
		if (!ft_strcmp(exec->words[i], "\n>\n"))
		{
			if (exec->wr_redir)
				redir_output_utils(&exec->wr_redir);
			exec->wr_redir = ft_strdup(exec->words[i + 1]);
			nbr = 1;
		}
		else if (!ft_strcmp(exec->words[i], "\n>>\n"))
		{
			if (exec->wr_redir)
				redir_output_utils(&exec->wr_redir);
			exec->wr_redir = ft_strdup(exec->words[i + 1]);
			nbr = 2;
		}
		i++;
	}
	return (nbr);
}

static int		redir_input_utils(char **dir)
{
	int fd;

	fd = open(*dir, O_RDONLY, 0777);
	if (fd == -1)
	{
		write(2, ": No such file or directory", 28);
		ft_putstr_fd(*dir, 2);
		write(2, "\n", 2);
		return (1);
	}
	free(*dir);
	*dir = NULL;
	return (0);
}

int		redir_input(t_exec *exec, int finish)
{
	int i;
	int nbr;

	i = exec->func_start[exec->i];
	nbr = 0;
	exec->redir_read = NULL;
	while (i < finish || (finish == -1 && exec->words[i]))
	{
		if (ft_strcmp(exec->words[i], "\n<\n") == 0)
		{
			if (exec->redir_read)
				if (redir_input_utils(&exec->redir_read))
					return (-1);
			exec->redir_read = ft_strdup(exec->words[i + 1]);
			nbr = 1;
		}
		i++;
	}
	return (nbr);
}

char	**get_fnct_args(t_exec *exec, int finish)
{
	char	**args;
	char	*tmp;
	int		i;

	args = NULL;
	i = exec->func_start[exec->i];
	while (i < finish || (finish == -1 && exec->words[i]))
	{
		if (!ft_strcmp(exec->words[i], "\n>\n")
			|| !ft_strcmp(exec->words[i], "\n<\n")
			|| !ft_strcmp(exec->words[i], "\n>>\n"))
			i++;
		else
		{
			tmp = ft_strdup(exec->words[i]);
			append_array(&args, &tmp);
		}
		i++;
	}
	return (args);
}
