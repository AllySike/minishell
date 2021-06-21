/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:23:39 by kgale             #+#    #+#             */
/*   Updated: 2021/04/27 16:19:56 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;
	int	wordstarted;

	i = 0;
	wordstarted = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			wordstarted = 1;
		else if (wordstarted == 1)
		{
			wordstarted = 0;
			words++;
		}
		i++;
	}
	if (wordstarted == 1)
		words++;
	return (words);
}

int	ft_find_word_start(int index, char const *s, char c)
{
	while (s[index] != '\0')
	{
		if (s[index] == c)
			index++;
		else
			return (index);
	}
	return (index);
}

int	f(int index, char const *s, char c)
{
	int	length;

	length = 0;
	while (s[index] != '\0' && s[index] != c)
	{
		length++;
		index++;
	}
	return (length);
}

int	define(int *in, char const *s, char c, int *words)
{
	*in = 0;
	*words = ft_count_words(s, c);
	return (0);
}

char	**my_split(char const *s)
{
	char	**o;
	int		in;
	int		i;
	int		words;
	int		j;

	if (s == NULL)
		return (NULL);
	i = define(&in, s, ' ', &words);
	o = (char **)malloc(sizeof(char *) * (words + 1));
	if (o == NULL)
		return (NULL);
	while (s[in] != '\0' && i < words && o != NULL)
	{
		in = ft_find_word_start(in, s, ' ');
		o[i] = (char *)malloc(sizeof(char) * (f(in, s, ' ') + 1));
		if (o[i] == NULL)
			return (NULL);
		j = 0;
		while ((s[in] != ' ' || i > 0) && s[in] != '\0')
			o[i][j++] = s[in++];
		o[i++][j] = '\0';
	}
	o[i] = NULL;
	return (o);
}
