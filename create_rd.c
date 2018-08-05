/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:28:13 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:28:15 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_road		*ft_createroad(void)
{
	t_road *newroad;

	newroad = (t_road*)malloc(sizeof(t_road));
	ft_memset(newroad, 0, sizeof(t_road));
	newroad->next = NULL;
	return (newroad);
}

void		ft_create_rd(t_roomlist **head, t_road **rd)
{
	t_roomlist		*end;
	t_roomlist		*buff;
	t_road			*new_room;

	end = *head;
	while (end->type != 2)
		end = end->next;
	(*rd) = (t_road*)malloc(sizeof(t_road));
	(*rd)->nameroom = end->name;
	(*rd)->busy = 0;
	(*rd)->next = NULL;
	while (end->from)
	{
		new_room = (t_road*)malloc(sizeof(t_road));
		new_room->next = (*rd);
		(*rd) = new_room;
		new_room->nameroom = end->from;
		(*rd)->busy = 0;
		buff = *head;
		while (ft_strcmp(buff->name, new_room->nameroom) != 0)
			buff = buff->next;
		end = buff;
	}
}
