/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_qts_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:54 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:11:35 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_utils(t_line *line, char *str)
{
	free_array(&line->env_parts);
	line->env_parts = ft_split(line->lst->content, '=');
	if (!ft_strcmp(line->env_parts[0], line->env_word))
	{
		line->tmp = line->curr;
		if (line->curr)
			line->curr = ft_strjoin(line->curr, line->env_parts[1]);
		else
			line->curr = ft_strdup(line->env_parts[1]);
		if (line->tmp)
			free(line->tmp);
		if (!str[line->i])
			append_array(&line->words_array, &line->curr);
		return (1);
	}
	return (0);
}

void	dbl_qts_utils(t_line *line, char *str, t_list *envp)
{
	line->i++;
	while (str[line->i] && str[line->i] != ' '
		&& str[line->i] != '$'
		&& str[line->i] != '\'' && str[line->i++] != '\"')
		line->env_word = append_arg(&line->env_word, str[line->i - 1]);
	line->lst = envp;
	while (line->lst != NULL)
	{
		if (cmp_utils(line, str))
			break ;
		line->lst = line->lst->next;
	}
	if (line->env_word)
	{
		free(line->env_word);
		line->env_word = NULL;
	}
}

static int	var_handle(t_line *line, char *str, t_list *envp)
{
	dbl_qts_utils(line, str, envp);
	if (line->lst == NULL)
	{
		if (!str[line->i])
		{
			append_array(&line->words_array,
				&line->curr);
			line->curr = NULL;
		}
		free_array(&line->env_parts);
		line->env_parts = NULL;
	}
	else
	{
		if (!str[line->i])
			line->curr = NULL;
		free_array(&line->env_parts);
		line->env_parts = NULL;
	}
	return (1);
}

static int	last_run_handle(int ret_val, t_line *line)
{
	line->i += 2;
	line->tmp = line->curr;
	if (line->curr)
		line->curr = ft_strjoin(line->curr, ft_itoa(ret_val));
	else
		line->curr = ft_strdup(ft_itoa(ret_val));
	if (line->tmp)
		free(line->tmp);
	return (1);
}

int	dbl_qts_handle(char *str, t_list *envp, int ret_val, t_line *line)
{
	if (str[line->i] == '\"')
		line->dbl_qts = 0;
	else if (str[line->i] == '\\')
	{
		if (str[line->i + 1] == '\\' || str[line->i + 1] == '\"'
			|| str[line->i + 1] == '$')
			line->i++;
		line->curr = append_arg(&line->curr, str[line->i]);
	}
	else if (str[line->i] == '$' && str[line->i + 1] == '?')
		return (last_run_handle(ret_val, line));
	else if (str[line->i] == '$' && str[line->i + 1])
		return (var_handle(line, str, envp));
	else
		line->curr = append_arg(&line->curr, str[line->i]);
	return (0);
}
