/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:07:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/26 17:52:31 by hasmith          ###   ########.fr       */
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

typedef struct		s_mast
{
	int				fd;
	int				start;
	int				end;
	char			*ln;
	int				j;
	int				y_len;
	char			**file;
	int				ants;
	char			*filename;
}					t_mast;

int     parce(t_mast *mast);

#endif