/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:34:01 by kgale             #+#    #+#             */
/*   Updated: 2021/09/16 10:57:43 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_arg(char **str, char c)
{
	char	*tmp;
	int		len;

	if (!*str)
	{
		tmp = (char *)malloc(sizeof(char) * (2));
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
	len = ft_strlen(*str);
	tmp = (char *)malloc(sizeof(char) * (len + 2));
	ft_strlcpy(tmp, *str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = 0;
	free(*str);
	return (tmp);
}

static int		array_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char ***array)
{
	char	**our_array;
	int		i;

	i = 0;
	our_array = *array;
	if (our_array == NULL)
		return ;
	while (our_array[i])
	{
		free(our_array[i]);
		i++;
	}
	free(our_array);
}

static char	**array_copy(char **array)
{
	int		i;
	char	**res;

	i = array_len(array);
	res = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (array[i])
	{
		res[i] = ft_strdup(array[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	append_array(char ***array, char **str)
{
	char **new_array;
	char **old_array;
	int		arr_len;

	old_array = *array;
	if (old_array == NULL)
	{
		*array = malloc(sizeof(char *) * 2);
		(*array)[1] = NULL;
		(*array)[0] = ft_strdup(*str);
		free(*str);
		return ;
	}
	new_array = array_copy(old_array);
	arr_len = array_len(old_array);
	new_array[arr_len] = ft_strdup(*str);
	new_array[arr_len + 1] = NULL;
	free(*str);
	free_array(array);
	*array = new_array;
}
