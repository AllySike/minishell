/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:32:31 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:25:35 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_utils(t_list **envp, char *array)
{
	char	**var1;
	char	**var;

	var = ft_split(array, '=');
	while (*envp)
	{
		var1 = ft_split((*envp)->content, '=');
		if (!ft_strcmp(var[0], var1[0]))
		{
			free((*envp)->content);
			free_array(&var1);
			(*envp)->content = ft_strdup(array);
			break ;
		}
		free_array(&var1);
		*envp = (*envp)->next;
	}
	free_array(&var);
}

void	ft_export(t_list **head, char **array)
{
	t_list	*envp;
	int		i;

	i = 1;
	if (!array[1])
		return ;
	while (array[i])
	{
		envp = *head;
		ft_export_utils(&envp, array[i]);
		if (!envp)
			ft_lstadd_back(head, ft_lstnew(ft_strdup(array[i])));
		i++;
	}
}

void	ft_declare(t_list *head, char **array)
{
	if (array[1] == NULL)
	{
		while (head)
		{
			write(1, "declare -x", 10);
			ft_putstr_fd((char *)head->content, 1);
			write(1, "\n", 1);
			head = head->next;
		}
	}
}
