/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:10:50 by kgale             #+#    #+#             */
/*   Updated: 2021/04/19 15:17:10 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r'
		|| c == '\b')
		return (1);
	return (0);
}

static int	ft_is_minus(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	helper(int minus)
{
	if (minus == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int				minus;
	long long int	output;
	int				i;

	i = 0;
	minus = 1;
	output = 0;
	while (ft_check_space(str[i]))
		i++;
	if (str[i] == '-')
		minus = ft_is_minus(str[i++]);
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			output = output * 10 + (str[i++] - 48);
			if (i >= 19)
				return (helper(minus));
		}
		else
			return (output * minus);
	}
	return (minus * output);
}
