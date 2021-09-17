/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:33:35 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:13:37 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = ft_strlen(dst);
	if (siz <= i)
		return (siz + ft_strlen(src));
	while (src[j] && j < siz - i - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count_s;

	count_s = 0;
	if (!dst && !src)
		return (0);
	while (src[count_s] && count_s + 1 < dstsize)
	{
		dst[count_s] = src[count_s];
		count_s++;
	}
	if (dstsize)
		dst[count_s] = '\0';
	while (src[count_s])
		count_s++;
	return (count_s);
}
