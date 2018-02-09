/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:07:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/09 01:34:32 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

typedef struct		s_res
{
	int				*qu;
	int				l1;
	int				l2;
	int				ants;
	struct s_res	*next;
}					t_res;

typedef struct		s_room
{
	int				visited;
	char			*room;
	int				c[2];
	int				prev;
	int				weight;
}					t_room;

typedef struct		s_links
{
	int				p;
	int				start;
	int				end;
	char			*id;
	char			*l1;
	int				l1_id;
	char			*l2;
	int				l2_id;
	int				weight;
	struct s_links	*next;
}					t_links;

typedef struct		s_mast
{
	int				fd;
	int				start;
	int				end;
	char			*ln;
	int				j;
	int				i;
	int				found;
	int				y_len;
	char			**file;
	char			*file_str;
	t_links			**hash_arr;
	int				ants;
	int				links;
	int				rooms;
	char			*filename;
	char			*start_string;
	char			**start_arr;
	char			***room_arr;
	t_room			**r_arr_st;
	t_res			*res;
	int				qsize;
	int				*path;
	char			***link_arr;
	char			*end_string;
	int				weight;
	int				**que;
	char			*new_str;
	int				cnt;
	int				cnt1;
	t_links			*tmp;
}					t_mast;

int					parse(t_mast *mast);
int					set_links(t_mast *mast);
int					valid_room(t_mast *mast);
void				make_arrs(t_mast *mast);
int					valid_link(t_mast *mast);
int					solve(t_mast *mast);
void				free_linked_arr(t_mast *mst);

#endif
