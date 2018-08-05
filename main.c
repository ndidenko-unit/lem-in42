/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:27:50 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:27:52 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_init(t_data *data)
{
	data->fd = 0;
	data->ants = 0;
	data->line = 0;
	data->roomtype = 0;
	data->start = 0;
	data->end = 0;
	data->connect = 0;
}

static void		ft_parsants(t_data *data)
{
	char *tmp;

	tmp = data->line;
	if (ft_strlen(data->line) > 7)
		EXITMSG;
	data->ants = ft_atoi(data->line);
	while (*(data->line))
	{
		if (ft_isdigit(*(data->line)))
			(data->line)++;
		else
			EXITMSG;
	}
	ft_putnbr(data->ants);
	write(1, "\n", 1);
	free(tmp);
}

static void			ft_parscommand(t_data *data)
{
	int len;

	len = ft_strlen(data->line);
	if (len == 1 || (len > 1 && data->line[1] != '#'))
		;
	else if (ft_strcmp(data->line, "##start") == 0)
	{
		if (data->start == 1)
			EXITMSG;
		data->start++;
		data->roomtype = 1;
	}
	else if (ft_strcmp(data->line, "##end") == 0)
	{
		if (data->end == 1)
			EXITMSG;
		data->end++;
		data->roomtype = 2;
	}
	else
		return ;
	ft_putstr(data->line);
	write(1, "\n", 1);
	free(data->line);
}

static void		ft_parsing(t_data *data, t_roomlist **head)
{
	while (get_next_line(data->fd, &data->line))
	{
		if (ft_strlen(data->line) < 1)
			EXITMSG;
		else if (data->ants == 0 && data->line != 0 && ft_isdigit(data->line[0]))
			ft_parsants(data);
		else if (data->line != 0 && data->line[0] == '#' && data->ants > 0)
			ft_parscommand(data);
		else if (data->line != 0 && data->line[0] != '#' &&
					data->line[0] != 'L' && ft_validroom(data->line) &&
												ft_cw(data->line) == 3)
			ft_room(data, head);
		else if (data->line != 0 && data->line[0] != 'L' &&
						ft_validlink(data->line) && ft_cw(data->line) == 2)
			ft_link(data, head);
		else
			EXITMSG;
	}
	ft_valid_start_end(head);
}

int				main(void)
{
	t_data		data;
	t_roomlist	*head;
	t_road		*rd;

	rd = NULL;
	head = NULL;
	ft_init(&data);
	if (data.fd == -1)
		EXITMSG;
	ft_parsing(&data, &head);
	ft_bfs(&head);
	ft_create_rd(&head, &rd);
	ft_let_my_people_go(&rd, data.ants);
	while (rd)
	{
		free(rd);
		rd = rd->next;
	}
	return (0);
}
