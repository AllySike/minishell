/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:46:23 by kgale             #+#    #+#             */
/*   Updated: 2021/04/22 17:53:10 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_buff	*ft_find_fd_in_lst(t_buff **lst, int fd)
{
	t_buff	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if (tmp && tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (ft_lstadd_bck(lst, NULL, 1, fd));
}

int	ft_read_fd(char **dst, const int fd, t_buff *elem)
{
	int		result;
	char	buff[2];
	int		flag;
	char	*dest;

	result = ft_init(&flag, fd, buff);
	while (flag != 1 && result)
	{
		if (result < 1)
			elem->end = 1;
		buff[result] = '\0';
		dest = *dst;
		*dst = ft_strjoin(*dst, buff);
		if (!*dst)
			return (-1);
		ft_empty(&flag, &dest);
		if (buff[0] == '\0')
			flag = 1;
		if (flag != 1)
			result = read(fd, buff, 1);
	}
	if (result == 0 && flag == 0)
		elem->end = 1;
	return (result);
}

int	ft_write_in_line(char **line, char *content)
{
	int	i;
	int	index;

	i = 0;
	while (content && content[i] && content[i] != '\0' && content[i] != '\n')
		i++;
	*line = (char *)malloc(sizeof(char) * (i + 1));
	if (!*line)
		return (0);
	index = 0;
	while (content && content[index] && index < i)
	{
		(*line)[index] = content[index];
		index++;
	}
	(*line)[index] = '\0';
	return (i);
}

int	ft_find_end_line_in_buff(char *str, t_buff **lst, int fd)
{
	t_buff	*curr;

	if (!str)
		return (0);
	while (*str)
		if (*str == '\0' || *str++ == '\n')
			return (0);
	curr = *lst;
	find_curr(curr, fd, lst);
	free(curr->content);
	free(curr);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int				res;
	char			*tmp;
	static t_buff	*lst;
	t_buff			*currelem;
	char			buff[2];

	currelem = ft_find_fd_in_lst(&lst, fd);
	if (fd < 0 || !line || read(fd, buff, 0) < 0
		|| !currelem)
		return (-1);
	tmp = currelem->content;
	res = ft_read_fd(&tmp, fd, currelem);
	if (!res && (!tmp || (tmp && !*tmp)))
		return (ft_ret(&line, &currelem, fd, &lst));
	currelem->content = tmp;
	res = ft_write_in_line(line, tmp);
	if (res == -1)
		return (-1);
	if (currelem->end && ft_find_end_line_in_buff(tmp, &lst, fd))
		return (0);
	else
		fd = 1;
	ft_strlcpy(&(tmp), &(tmp[res + 1]), my_strlen(tmp) - res, 0);
	return (fd);
}
