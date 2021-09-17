/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:29:46 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:29:46 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_operator(char *str, t_line *line)
{
	if (line->curr)
	{
		append_array(&line->words_array, &line->curr);
		line->curr = NULL;
	}
	line->curr = append_arg(&line->curr, '\n');
	line->curr = append_arg(&line->curr, str[line->i]);
	line->curr = append_arg(&line->curr, str[line->i + 1]);
	line->curr = append_arg(&line->curr, '\n');
	append_array(&line->words_array, &line->curr);
	line->curr = NULL;
	line->i++;
}

static void	operators_utils(char *str, t_line *line)
{
	if (str[line->i] == '>' && str[line->i + 1] == '>')
		redir_operator(str, line);
	else if (str[line->i] == '\'')
		line->sngl_qts = 1;
	else if (str[line->i] == '\"')
		line->dbl_qts = 1;
	else if (str[line->i] == '\\')
	{
		line->i++;
		line->curr = append_arg(&line->curr, str[line->i]);
	}
	else if (str[line->i] == ' ')
	{
		append_array(&line->words_array, &line->curr);
		line->curr = NULL;
	}
}

static int	operators(char *str, t_line *line)
{
	if ((str[line->i] == '>' && str[line->i + 1] != '>')
		|| str[line->i] == '<' || str[line->i] == '|'
		|| str[line->i] == ';')
	{
		if (line->curr)
		{
			append_array(&line->words_array, &line->curr);
			line->curr = NULL;
		}
		line->curr = append_arg(&line->curr, '\n');
		line->curr = append_arg(&line->curr, str[line->i]);
		line->curr = append_arg(&line->curr, '\n');
		append_array(&line->words_array, &line->curr);
		line->curr = NULL;
		return (1);
	}
	else if ((str[line->i] == '>' && str[line->i + 1] == '>')
		|| str[line->i] == '\'' || str[line->i] == '\"'
		|| str[line->i] == '\\' || str[line->i] == ' ')
	{
		operators_utils(str, line);
		return (1);
	}
	return (0);
}

int	symb_handle(char *str, t_list *envp, int ret, t_line *line)
{
	while (str[line->i] == ' ' && !line->curr)
		line->i++;
	if (operators(str, line))
		NULL;
	else if (str[line->i] == '$' && str[line->i + 1] == '?')
	{
		line->i += 2;
		line->tmp = line->curr;
		if (line->curr)
			line->curr = ft_strjoin(line->curr, ft_itoa(ret));
		else
			line->curr = ft_strdup(ft_itoa(ret));
		if (line->tmp)
			free(line->tmp);
		return (1);
	}
	else if (str[line->i] == '$' && str[line->i + 1])
		return (handle_dollar(str, line, envp));
	else
		line->curr = append_arg(&line->curr, str[line->i]);
	return (0);
}
