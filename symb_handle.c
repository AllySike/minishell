/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symb_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:05:16 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:05:16 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input_utils(t_line *line,
	char *str, t_list *envp, int ret_val)
{
	while (str[line->i])
	{
		if (!line->dbl_qts && !line->sngl_qts)
		{
			if (symb_handle(str, envp, ret_val, line))
				continue ;
		}
		else if (line->dbl_qts)
		{
			if (dbl_qts_handle(str, envp, ret_val, line))
				continue ;
		}
		else
		{
			if (str[line->i] == '\'')
				line->sngl_qts = 0;
			else
				line->curr = append_arg(&line->curr, str[line->i]);
		}
		line->i++;
	}
}

char	**process_inputs(char *str, t_list *envp, int ret_val)
{
	t_line	line;

	line.i = 0;
	line.dbl_qts = 0;
	line.sngl_qts = 0;
	line.curr = NULL;
	line.env_word = NULL;
	line.env_parts = NULL;
	line.words_array = NULL;
	process_input_utils(&line, str, envp, ret_val);
	if (line.curr && *line.curr)
		append_array(&line.words_array, &line.curr);
	return (line.words_array);
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
