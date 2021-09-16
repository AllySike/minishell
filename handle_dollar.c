/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:33:38 by kgale             #+#    #+#             */
/*   Updated: 2021/09/13 13:14:55 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_lst(char *str, t_processor *processor)
{
	while (processor->lst)
	{
		free_array(&processor->env_parts);
		processor->env_parts = ft_split(processor->lst->content, '=');
		if (ft_strcmp(processor->env_parts[0], processor->env_word) == 0)
		{
			processor->tmp = processor->curr;
			if (processor->curr)
				processor->curr = ft_strjoin(processor->curr,
				processor->env_parts[1]);
			else
				processor->curr = ft_strdup(processor->env_parts[1]);
			if (processor->tmp)
				free(processor->tmp);
			if (!str[processor->i] || str[processor->i] == ' '
				|| str[processor->i] == '|' || str[processor->i] == ';'
				|| str[processor->i] == '>' || str[processor->i] == '<')
				append_array(&processor->words_array,
				&processor->curr);
			break ;
		}
		processor->lst = processor->lst->next;
	}
}

static int	envp_parts(char *str, t_processor *processor)
{
	if (processor->lst == NULL)
	{
		if (!str[processor->i] || str[processor->i] == ' '
			|| str[processor->i] == '|' || str[processor->i] == ';'
			|| str[processor->i] == '>' || str[processor->i] == '<')
		{
			if (processor->curr)
				append_array(&processor->words_array,
				&processor->curr);
			processor->curr = NULL;
		}
		free_array(&processor->env_parts);
		processor->env_parts = NULL;
		return (1);
	}
	else
	{
		if (!str[processor->i] || str[processor->i] == ' '
			|| str[processor->i] == '|' || str[processor->i] == ';'
			|| str[processor->i] == '>' || str[processor->i] == '<')
			processor->curr = NULL;
		free_array(&processor->env_parts);
		processor->env_parts = NULL;
		return (1);
	}
}

int	handle_dollar(char *str, t_processor *processor, t_list *envp)
{
	processor->i++;
	while (str[processor->i] && str[processor->i]
			!= ' ' && str[processor->i] != '$'
			&& str[processor->i] != '\'' && str[processor->i] != '\"'
			&& str[processor->i] != '|' && str[processor->i] != ';'
			&& str[processor->i] != '>' && str[processor->i] != '<')
	{
		processor->env_word =
				append_arg(&processor->env_word, str[processor->i]);
		processor->i++;
	}
	processor->lst = envp;
	process_lst(str, processor);
	if (processor->env_word)
	{
		free(processor->env_word);
		processor->env_word = NULL;
	}
	envp_parts(str, processor);
	return (1);
}
