/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:29:11 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:29:13 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				ft_validroom(char *data)
{
	int space;
	int len;

	space = 0;
	len = ft_strlen(data);
	while (*data != ' ' && *data != '\0')
		data++;
	while (*data)
	{
		if (!ft_isdigit(*data) && *data != ' ')
			return (0);
		else if (*data == ' ' && *data + 1 == ' ')
			return (0);
		else if (*data == ' ')
			space++;
		data++;
	}
	if (space != 2)
		return (0);
	data = data - len;
	ft_putstr(data);
	write(1, "\n", 1);
	return (1);
}

int				ft_validlink(char *data)
{
	int hyphen;
	int len;

	hyphen = 0;
	len = ft_strlen(data);
	while (*data)
	{
		if (*data == ' ')
			return (0);
		else if (*data == '-')
			hyphen++;
		data++;
	}
	if (hyphen != 1)
		return (0);
	data = data - len;
	return (1);
}

void			ft_valid_start_end(t_roomlist **head)
{
	int			type1;
	int			type2;
	t_roomlist	*tmp;

	type1 = 0;
	type2 = 0;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == 1)
			type1++;
		else if (tmp->type == 2)
			type2++;
		tmp = tmp->next;
	}
	if (type1 != 1 || type2 != 1)
		EXITMSG;
}

static int		ft_is_spacer(char c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '-'
			|| c == '\f' || c == '\r' || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int				ft_cw(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (ft_is_spacer(*str) == 0 && ft_is_spacer(*(str + 1)) == 1)
			count++;
		str++;
	}
	return (count);
}
