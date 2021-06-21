/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:25:52 by kgale             #+#    #+#             */
/*   Updated: 2021/04/27 16:19:02 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			if (s[i] == (char)c)
				return ((char *)&s[i]);
			i++;
		}
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**o;
	int		in;
	int		i;
	int		words;
	int		j;

	if (s == NULL)
		return (NULL);
	i = define(&in, s, c, &words);
	o = (char **)malloc(sizeof(char *) * (words + 1));
	if (o == NULL)
		return (NULL);
	while (s[in] != '\0' && i < words && o != NULL)
	{
		in = ft_find_word_start(in, s, c);
		o[i] = (char *)malloc(sizeof(char) * (f(in, s, c) + 1));
		if (o[i] == NULL)
			return (NULL);
		j = 0;
		while (s[in] != c && s[in] != '\0')
			o[i][j++] = s[in++];
		o[i++][j] = '\0';
	}
	o[i] = NULL;
	return (o);
}
