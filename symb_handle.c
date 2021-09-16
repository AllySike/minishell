/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:32:41 by kgale             #+#    #+#             */
/*   Updated: 2021/09/12 22:04:51 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input_utils(t_processor *processor,
	char *str, t_list *envp, int ret_val)
{
	while (str[processor->i])
	{
		if (!processor->dbl_qts && !processor->sngl_qts)
		{
			if(symb_handle(str, envp, ret_val, processor))
				continue;
		}
		else if (processor->dbl_qts)
		{
			if (dbl_qts_handle(str, envp, ret_val, processor))
				continue;
		}
		else
		{
			if (str[processor->i] == '\'')
				processor->sngl_qts = 0;
			else
				processor->curr = append_arg(&processor->curr, str[processor->i]);
		}
		processor->i++;
	}
}

char	**process_inputs(char *str, t_list *envp, int ret_val)
{
	t_processor processor;

	processor.i = 0;
	processor.dbl_qts = 0;
	processor.sngl_qts = 0;
	processor.curr = NULL;
	processor.env_word = NULL;
	processor.env_parts = NULL;
	processor.words_array = NULL;
	process_input_utils(&processor, str, envp, ret_val);
	if (processor.curr && *processor.curr)
		append_array(&processor.words_array, &processor.curr);
	return (processor.words_array);
}

char	**ft_lstarr(t_list *lst)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(lst);
	array = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		array[i] = lst->content;
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
