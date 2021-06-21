/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:23:39 by kgale             #+#    #+#             */
/*   Updated: 2021/02/05 15:13:20 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = len;
	while (--len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}
