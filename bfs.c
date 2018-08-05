/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:27:24 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:27:26 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_cmp_queue(t_road *start_queue, char *name)
{
	while (start_queue)
	{
		if (!ft_strcmp(start_queue->nameroom, name))
			return (0);
		start_queue = start_queue->next;
	}
	return (1);
}

static void		ft_start_queue(t_roomlist *tmp, t_road **start_queue)
{
	t_road	*new_road;
	int		i;

	i = 1;
	while (tmp->type != 1)
		tmp = tmp->next;
	tmp->use = 1;
	if (!tmp->link)
		EXITMSG;
	new_road = ft_createroad();
	*start_queue = new_road;
	new_road->nameroom = tmp->link[0]->name;
	tmp->link[0]->from = tmp->name;
	while (tmp->link[i])
	{
		new_road->next = ft_createroad();
		new_road = new_road->next;
		new_road->nameroom = tmp->link[i]->name;
		tmp->link[i]->from = tmp->name;
		i++;
	}
}

static void		ft_create_next_queue(t_road *start_queue, t_road **end_queue,
															t_roomlist *tmp)
{
	int		i;
	t_road	*new_road;

	i = 0;
	while (tmp->link[i])
	{
		if (tmp->link[i]->use != 1)
		{
			if (ft_cmp_queue(start_queue, tmp->link[i]->name))
			{
				new_road = ft_createroad();
				new_road->nameroom = tmp->link[i]->name;
				tmp->link[i]->from = tmp->name;
				while ((*end_queue)->next)
					(*end_queue) = (*end_queue)->next;
				(*end_queue)->next = new_road;
			}
		}
		i++;
	}
}

static void		ft_next_queue(t_roomlist *head, t_roomlist *tmp,
											t_road *start_queue)
{
	t_road *end_queue;

	end_queue = start_queue;
	while (tmp)
	{
		if (!start_queue)
			EXITMSG;
		if (ft_strcmp(tmp->name, start_queue->nameroom) == 0)
		{
			tmp->use = 1;
			ft_create_next_queue(start_queue, &end_queue, tmp);
			if (tmp->type == 2)
				break ;
			start_queue = start_queue->next;
			tmp = head;
			continue ;
		}
		tmp = tmp->next;
	}
}

void			ft_bfs(t_roomlist **head)
{
	t_roomlist	*tmp;
	t_road		*start_queue;

	tmp = *head;
	start_queue = NULL;
	ft_start_queue(tmp, &start_queue);
	if (start_queue == NULL)
		EXITMSG;
	ft_next_queue(*head, tmp, start_queue);
	while (start_queue)
	{
		free(start_queue);
		start_queue = start_queue->next;
	}
}
