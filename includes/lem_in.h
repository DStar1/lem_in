/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:07:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/01 18:27:33 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "../libft/libft.h"

/*
** visualizer
*/

typedef struct		s_vis
{
	int				*img_int;
	void			*mlx_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	void			*mlx;
	void			*win;
	int				wsize;
}					t_vis;

typedef struct		s_links
{
	int				p;//index id
	int				start;//start index
	int				end;//end index
	char			*id;
	char			*l1;
	int				l1_id;
	char			*l2;
	int				l2_id;
	int				weight;
	struct	s_links	*next;
}					t_links;

typedef struct		s_mast
{
	int				fd;
	int				start;//index of start in room_arr
	int				end;//index of end in room_arr
	char			*ln;
	int				j;
	int				i;
	int				y_len;
	char			**file;
	t_links			**hash_arr;//t_links
	int				ants;
	int				links;
	int				rooms;
	char			*filename;
	char			*start_string;
	char			**start_arr;
	char			***room_arr;
	char			***link_arr;
	char			*end_string;
}					t_mast;

int     parse(t_mast *mast);
int		set_links(t_mast *mast);
int		valid_room(t_mast *mast);
void	make_arrs(t_mast *mast);
int		valid_link(t_mast *mast);

#endif