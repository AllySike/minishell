/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:47:19 by kgale             #+#    #+#             */
/*   Updated: 2021/04/19 15:52:01 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	my_strlen(const char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

void	ft_strl_cpy(char **dst, const char *src, int siz, int index)
{
	size_t	i;

	i = 0;
	while (--siz >= 0 && src[i])
	{
		dst[0][i + index] = src[i];
		i++;
	}
	dst[0][i + index] = '\0';
	while (dst[0][i + index] != '\0')
		i++;
	while (dst[0][i + index])
		dst[0][i++] = '\0';
}

t_buff	*ft_lstnw(char *content, t_buff *elem, int len, int fd)
{
	if (!content)
	{
		elem->content = NULL;
		elem->fd = fd;
		elem->end = 0;
	}
	else
		ft_strl_cpy(&(elem->content), content, len, 0);
	return (elem);
}

t_buff	*ft_lstadd_bck(t_buff **lst, char *content, int len, int fd)
{
	void	*f;
	t_buff	*elem;

	elem = (t_buff *)malloc(sizeof(t_buff));
	if (elem)
	{
		(ft_lstnw(content, elem, len, fd))->next = NULL;
		if (lst && elem)
		{
			if (elem && *lst)
			{
				f = *lst;
				while (*lst != NULL && (*lst)->next)
					*lst = (*lst)->next;
				(*lst)->next = elem;
				*lst = f;
			}
			else if (!*lst && elem)
				*lst = elem;
		}
	}
	return (elem);
}
