/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:25:47 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:25:51 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:24:47 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:24:49 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_lst(char *str, t_line *line)
{
	while (line->lst)
	{
		free_array(&line->env_parts);
		line->env_parts = ft_split(line->lst->content, '=');
		if (ft_strcmp(line->env_parts[0], line->env_word) == 0)
		{
			line->tmp = line->curr;
			if (line->curr)
				line->curr = ft_strjoin(line->curr, line->env_parts[1]);
			else
				line->curr = ft_strdup(line->env_parts[1]);
			if (line->tmp)
				free(line->tmp);
			if (!str[line->i] || str[line->i] == ' '
				|| str[line->i] == '|' || str[line->i] == ';'
				|| str[line->i] == '>' || str[line->i] == '<')
				append_array(&line->words_array, &line->curr);
			break ;
		}
		line->lst = line->lst->next;
	}
}

static int	envp_parts(char *str, t_line *line)
{
	if (line->lst == NULL)
	{
		if (!str[line->i] || str[line->i] == ' '
			|| str[line->i] == '|' || str[line->i] == ';'
			|| str[line->i] == '>' || str[line->i] == '<')
		{
			if (line->curr)
				append_array(&line->words_array, &line->curr);
			line->curr = NULL;
		}
		free_array(&line->env_parts);
		line->env_parts = NULL;
		return (1);
	}
	else
	{
		if (!str[line->i] || str[line->i] == ' '
			|| str[line->i] == '|' || str[line->i] == ';'
			|| str[line->i] == '>' || str[line->i] == '<')
			line->curr = NULL;
		free_array(&line->env_parts);
		line->env_parts = NULL;
		return (1);
	}
}

int	handle_dollar(char *str, t_line *line, t_list *envp)
{
	line->i++;
	while (str[line->i] && str[line->i]
		!= ' ' && str[line->i] != '$'
		&& str[line->i] != '\'' && str[line->i] != '\"'
		&& str[line->i] != '|' && str[line->i] != ';'
		&& str[line->i] != '>' && str[line->i] != '<')
	{
		line->env_word = append_arg(&line->env_word, str[line->i]);
		line->i++;
	}
	line->lst = envp;
	process_lst(str, line);
	if (line->env_word)
	{
		free(line->env_word);
		line->env_word = NULL;
	}
	envp_parts(str, line);
	return (1);
}
