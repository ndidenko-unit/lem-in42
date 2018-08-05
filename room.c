/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:28:01 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:28:03 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_roomlist	*ft_createroom(void)
{
	t_roomlist	*newroom;

	newroom = (t_roomlist*)malloc(sizeof(t_roomlist));
	ft_memset(newroom, 0, sizeof(t_roomlist));
	newroom->next = NULL;
	return (newroom);
}

static void			ft_freeroom(char **splitroom, t_data *data)
{
	free(splitroom[0]);
	free(splitroom[1]);
	free(splitroom[2]);
	free(splitroom);
	free(data->line);
}

static void			ft_valid2room(t_roomlist *newroom, t_roomlist *head)
{
	while (head)
	{
		if (ft_strcmp((head)->name, newroom->name) == 0)
			EXITMSG;
		if ((head)->x == newroom->x && (head)->y == newroom->y)
			EXITMSG;
		head = (head)->next;
	}
}

void				ft_room(t_data *data, t_roomlist **head)
{
	t_roomlist	*newroom;
	t_roomlist	*tmproom;
	char		**splitroom;

	newroom = ft_createroom();
	newroom->type = data->roomtype;
	data->roomtype = 0;
	splitroom = ft_strsplit(data->line, ' ');
	newroom->name = ft_strdup(splitroom[0]);
	newroom->x = ft_atoi(splitroom[1]);
	newroom->y = ft_atoi(splitroom[2]);
	ft_valid2room(newroom, *head);
	if (!(*head))
	{
		*head = newroom;
		ft_freeroom(splitroom, data);
		return ;
	}
	tmproom = *head;
	while (tmproom->next != NULL)
		tmproom = tmproom->next;
	tmproom->next = newroom;
	ft_freeroom(splitroom, data);
}
