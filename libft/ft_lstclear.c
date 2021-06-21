/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:22:32 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:12:33 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	void	*ref;

	if (lst && *lst)
	{
		while (*lst)
		{
			ref = (void *)(*lst)->next;
			(*del)(*lst);
			*lst = ref;
		}
		*lst = NULL;
	}
}
