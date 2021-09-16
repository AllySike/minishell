/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:35:13 by kgale             #+#    #+#             */
/*   Updated: 2021/09/16 12:03:16 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list **head, char **array)
{
	t_list	*p;
	t_list	*q;
	char	**value;
	int		i;

	i = 1;
	while (array[i])
	{
		p = *head;
		q = *head;
		value = ft_split((*head)->content, '=');
		if (ft_strcmp(array[i], value[0]) == 0)
		{
			*head = (*head)->next;
			free(p);
			return ;
		}
		else
		{
			while (p)
			{
				free_array(&value);
				value = ft_split((p)->content, '=');
				if (!ft_strcmp(array[i], value[0]))
				{
					q->next = p->next;
					free(p);
					break ;
				}
				else
				{
					q = p;
					p = p->next;
				}
			}
		}
		free_array(&value);
		i++;
	}
}
