/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:16:15 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:13:07 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;
	int			i;

	if (src != NULL && dst != NULL)
	{
		dest = dst;
		source = src;
		i = 0;
		while (n-- > 0)
		{
			dest[i++] = *source++;
		}
	}
	return (dst);
}
