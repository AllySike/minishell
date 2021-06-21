/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:55:57 by kgale             #+#    #+#             */
/*   Updated: 2021/04/19 16:47:43 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_empty(int *flag, char **dest)
{
	free(*dest);
	*flag = 0;
}

int	ft_init(int *flag, int fd, char buff[2])
{
	*flag = 0;
	return (read(fd, buff, 1));
}

void	find_curr(t_buff	*curr, int fd, t_buff **lst)
{
	t_buff	*next;

	if (curr->fd == fd)
		*lst = curr->next;
	else
	{
		while (curr && curr->next)
		{
			next = curr->next;
			if (next->fd == fd)
			{
				curr->next = next->next;
				curr = next;
				break ;
			}
			curr = curr->next;
		}
	}
}

int	ft_ret(char ***line, t_buff **currelem, int fd, t_buff **lst)
{
	ft_write_in_line(*line, (*currelem)->content);
	ft_find_end_line_in_buff((*currelem)->content, &(*lst), fd);
	return (0);
}
