/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:19:29 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:12:57 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*scan;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	scan = (char *)s;
	while (n-- > 0)
	{
		if (scan[i] == (int)c)
			return ((void *)&scan[i]);
		i++;
	}
	return (NULL);
}
