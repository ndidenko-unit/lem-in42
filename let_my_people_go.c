/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_my_people_go.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:28:32 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:28:34 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_anthill(t_ants **anthill, t_road **rd, int ants)
{
	t_ants	one_ant;
	int		i;

	i = 0;
	(*anthill) = (t_ants*)malloc(sizeof(t_ants) * ants);
	while (i < ants)
	{
		one_ant.room = (*rd);
		one_ant.antnbr = i + 1;
		one_ant.finish = 0;
		(*anthill)[i] = one_ant;
		i++;
	}
}

static void		ft_printstep2(t_ants **anthill, t_road **end, int i)
{
	(*end)->antinroom++;
	(*anthill)[i].finish++;
	(*anthill)[i].room->busy = 0;
}

static void		ft_printstep(t_ants **anthill, t_road **end, int ants)
{
	int		i;
	int		print;

	i = 0;
	print = 0;
	while (i < ants)
	{
		if ((*anthill)[i].room->next != NULL &&
						(*anthill)[i].room->next->busy == 0)
		{
			if (print == 1)
				write(1, " ", 1);
			(*anthill)[i].room->next->busy = 1;
			(*anthill)[i].room->busy = 0;
			(*anthill)[i].room = (*anthill)[i].room->next;
			write(1, "L", 1);
			ft_putnbr((*anthill)[i].antnbr);
			write(1, "-", 1);
			ft_putstr((*anthill)[i].room->nameroom);
			print = 1;
		}
		else if ((*anthill)[i].room->next == NULL && !(*anthill)[i].finish)
			ft_printstep2(anthill, end, i);
		i++;
	}
}

void			ft_let_my_people_go(t_road **rd, int ants)
{
	t_ants	*anthill;
	t_road	*end;

	end = (*rd);
	ft_anthill(&anthill, rd, ants);
	while (end->next != NULL)
		end = end->next;
	write(1, "\n", 1);
	while (end->antinroom != ants)
	{
		ft_printstep(&anthill, &end, ants);
		if (end->antinroom != ants)
			write(1, "\n", 1);
	}
	free(anthill);
}
