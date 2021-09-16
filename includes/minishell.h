/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:00:26 by bannette          #+#    #+#             */
/*   Updated: 2021/09/16 12:02:42 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct	s_all
{
	char	*line;
	char	*command;
	int		read_bytes;
	int		max_indx;
	int		line_len;
	t_list	*history;
	t_list	*envp;
	int		ret;
}				t_all;

typedef struct	s_command_set
{
	char	**argv;
	char	*separators;
	int		*indxs_separators;
	int		db_quotes_flag;
	int		sg_quotes_flag;
}				t_command_set;

typedef struct	s_exec
{
	char	**words;
	int		i;
	int		pid;
	int		func_cnt;
	int		*func_start;
	char	**func_args;
	char	*wr_redir;
	char	*redir_read;
	int		*pipe_start;
	int		*writing_from_pipes;
	int		wr_redir_case;
	int		r_redir_case;
	int		fd;
	int		pipe_cnt;
	int		**pipes_fds;
	int		j;
	int		wstatus;
	int		ret;
}				t_exec;

typedef struct	s_processor
{
	int		dbl_qts;
	int		sngl_qts;
	char	**words_array;
	char	*curr;
	char	*tmp;
	char	*env_word;
	char	**env_parts;
	t_list	*lst;
	int		i;
}				t_processor;

void	append_array(char ***array, char **str);
char	*append_arg(char **str, char c);
int		dbl_qts_handle(char *str, t_list *envp, int ret_val, t_processor *processor);
void	exec(t_all *all);
int		exec_init(t_exec *exec, t_all *all);
void	exec_init_utils(t_exec *exec);
void	ft_chdir(char **array, t_list **head);
void	ft_env(t_list *envp);
void	ft_declare(t_list *head, char **array);
void	ft_echo(char **array);
void	ft_export(t_list **head, char **array);
void	ft_pwd(char **array);
void	ft_unset(t_list **head, char **array);
void	free_array(char ***array);
char	**get_fnct_args(t_exec *exec, int finish);
int		get_line(char **str);
int		handle_dollar(char *str, t_processor *processor, t_list *envp);
void	input_helper(t_all *all);
void	input_management(t_all *all, int *cnt);
char	**ft_lstarr(t_list *lst);
void	pid_create(t_exec *exec, t_list **list_envp);
char	**process_inputs(char *str, t_list *envp, int ret_val);
int		redir_input(t_exec *exec, int finish);
int		redir_output(t_exec *exec, int finish);
int		symb_handle(char *str, t_list *envp, int ret, t_processor *processor);
void	terminal_setup(void);

#endif
