/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 09:47:45 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:13:25 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	if (s1 == NULL || s2 == NULL || !n)
		return (0);
	i = 0;
	if (!*s1 || !*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (--n && str1[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
