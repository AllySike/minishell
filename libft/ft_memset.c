/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:51:45 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:14:01 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*dest;

	if (b == NULL)
		return (NULL);
	dest = b;
	while (len-- > 0)
	{
		*dest++ = c;
	}
	return (b);
}
