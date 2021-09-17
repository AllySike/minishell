/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:31:39 by kgale             #+#    #+#             */
/*   Updated: 2021/09/17 14:09:49 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_pwd(t_list **head, char *dir)
{
	t_list	*envp;
	char	**var;

	envp = *head;
	var = NULL;
	while (envp)
	{
		var = ft_split(envp->content, '=');
		if (!ft_strcmp("PWD", var[0]))
		{
			free(envp->content);
			free_array(&var);
			envp->content = ft_strjoin("PWD=", dir);
			return ;
		}
		free_array(&var);
		envp = envp->next;
	}
}

static void	ft_add_old_pwd(t_list **head, char *dir)
{
	t_list	*envp;
	char	**var;
	char	*tmp;

	envp = *head;
	var = NULL;
	while (envp)
	{
		var = ft_split(envp->content, '=');
		if (!ft_strcmp("OLDPWD", var[0]))
		{
			tmp = envp->content;
			envp->content = ft_strjoin("OLDPWD=", dir);
			if (tmp)
				free(tmp);
			free_array(&var);
			return ;
		}
		free_array(&var);
		envp = envp->next;
	}
	ft_lstadd_back(head, ft_lstnew(ft_strjoin("OLDPWD=", dir)));
}

static void	ft_chdir_help(char **array, char *dir, char *search, t_list **head)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		free(search);
		return ;
	}
	getcwd(dir, 50000);
	if (!chdir(search))
	{
		ft_add_old_pwd(head, dir);
		ft_bzero(dir, ft_strlen(dir));
		getcwd(dir, 50000);
		ft_add_pwd(head, dir);
	}
	else
	{
		ft_putstr_fd(search, 2);
		write(2, ": cd: no such file or directory\n", 33);
	}
	free(search);
}

static char	*find_home(t_list **head)
{
	t_list	*envp;
	char	**var1;
	char	*res;

	envp = *head;
	var1 = NULL;
	while (envp)
	{
		var1 = ft_split(envp->content, '=');
		if (!ft_strcmp("HOME", var1[0]))
		{
			res = ft_strdup(var1[1]);
			free_array(&var1);
			return (res);
		}
		free_array(&var1);
		envp = envp->next;
	}
	return (NULL);
}

void	ft_chdir(char **array, t_list **head)
{
	char	*search;
	char	dir[50000];

	search = NULL;
	if (array[1])
		search = ft_strdup(array[1]);
	else
	{
		search = find_home(head);
		if (!search)
		{
			write(2, " cd: HOME not set\n", 19);
			free(search);
			return ;
		}
	}
	ft_chdir_help(array, dir, search, head);
}
