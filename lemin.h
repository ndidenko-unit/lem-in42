/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:27:33 by ndidenko          #+#    #+#             */
/*   Updated: 2018/08/03 13:27:34 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# define EXITMSG (exit(write(2, "ERROR\n", 6)))

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct			s_data
{
	int					fd;
	int					ants;
	char				*line;
	int					roomtype;
	int					start;
	int					end;
	int					connect;
}						t_data;

typedef	struct			s_roomlist
{
	struct s_roomlist	**link;
	char				*name;
	int					type;
	int					x;
	int					y;
	int					use;
	char				*from;
	struct s_roomlist	*next;
}						t_roomlist;

typedef struct			s_road
{
	char				*nameroom;
	int					busy;
	int					antinroom;
	struct s_road		*next;
}						t_road;

typedef struct			s_ants
{
	int					antnbr;
	int					finish;
	struct s_road		*room;
}						t_ants;

void					ft_room(t_data *data, t_roomlist **head);
void					ft_link(t_data *data, t_roomlist **head);
void					ft_bfs(t_roomlist **head);
void					ft_create_rd(t_roomlist **head, t_road **rd);
t_road					*ft_createroad(void);
void					ft_let_my_people_go(t_road **rd, int ants);
int						ft_validroom(char *data);
int						ft_validlink(char *data);
void					ft_valid_start_end(t_roomlist **head);
int						ft_cw(char *str);

#endif
