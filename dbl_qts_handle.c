/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_qts_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:54 by kgale             #+#    #+#             */
/*   Updated: 2021/09/14 19:50:38 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_utils(t_processor *processor, char *str)
{
	free_array(&processor->env_parts);
	processor->env_parts = ft_split(processor->lst->content, '=');
	if (!ft_strcmp(processor->env_parts[0], processor->env_word))
	{
		processor->tmp = processor->curr;
		if (processor->curr)
			processor->curr =
			ft_strjoin(processor->curr, processor->env_parts[1]);
		else
			processor->curr = ft_strdup(processor->env_parts[1]);
		if (processor->tmp)
			free(processor->tmp);
		if (!str[processor->i])
			append_array(&processor->words_array, &processor->curr);
		return (1);
	}
	return (0);
}


void	dbl_qts_utils(t_processor *processor, char *str, t_list *envp)
{
	processor->i++;
	while (str[processor->i] && str[processor->i] != ' '
			&& str[processor->i] != '$'
			&& str[processor->i] != '\'' && str[processor->i++] != '\"')
		processor->env_word = append_arg(&processor->env_word, str[processor->i - 1]);
	processor->lst = envp;
	while (processor->lst != NULL)
	{
		if (cmp_utils(processor, str))
			break ;
		processor->lst = processor->lst->next;
	}
	if (processor->env_word)
	{
		free(processor->env_word);
		processor->env_word = NULL;
	}
}

static int	var_handle(t_processor *processor, char *str, t_list *envp)
{
	dbl_qts_utils(processor, str, envp);
	if (processor->lst == NULL)
	{
		if (!str[processor->i])
		{
			append_array(&processor->words_array,
			&processor->curr);
			processor->curr = NULL;
		}
		free_array(&processor->env_parts);
		processor->env_parts = NULL;
	}
	else
	{
		if (!str[processor->i])
			processor->curr = NULL;
		free_array(&processor->env_parts);
		processor->env_parts = NULL;
	}
	return (1);
}

static int	last_run_handle(int ret_val, t_processor *processor)
{
	processor->i += 2;
	processor->tmp = processor->curr;
	if (processor->curr)
		processor->curr = ft_strjoin(processor->curr, ft_itoa(ret_val));
	else
		processor->curr = ft_strdup(ft_itoa(ret_val));
	if (processor->tmp)
		free(processor->tmp);
	return (1);
}

int		dbl_qts_handle(char *str, t_list *envp, int ret_val, t_processor *processor)
{
	if (str[processor->i] == '\"')
		processor->dbl_qts = 0;
	else if (str[processor->i] == '\\')
	{
		if (str[processor->i + 1] == '\\' || str[processor->i + 1] == '\"'
			|| str[processor->i + 1] == '$')
			processor->i++;
		processor->curr = append_arg(&processor->curr, str[processor->i]);
	}
	else if (str[processor->i] == '$' && str[processor->i + 1] == '?')
		return (last_run_handle(ret_val, processor));
	else if (str[processor->i] == '$' && str[processor->i + 1])
		return (var_handle(processor, str, envp));
	else
		processor->curr = append_arg(&processor->curr, str[processor->i]);
	return (0);
}
