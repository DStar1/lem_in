/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:35:29 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 20:24:46 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	make_arrs(t_mast *mast)
{
	int r;
	int l;
	int i;
	char **tmp;

	r = 0;
	l = 0;
	mast->j = 0;
	mast->r_arr_st = (t_room**)ft_memalloc(sizeof(t_room*) * mast->rooms);
	mast->link_arr = (char***)ft_memalloc(sizeof(char**) * mast->links + 1);
	while (mast->file[mast->j])
	{
		if (valid_room(mast) == 1)
		{
			mast->r_arr_st[r] = (t_room*)ft_memalloc(sizeof(t_room));
			tmp = ft_strsplit(mast->file[mast->j], ' ');
			mast->r_arr_st[r]->room = tmp[0];
			if (ft_isnbr(tmp[1]) && ft_isnbr(tmp[2]))//change to numbers for the coordinates of the struct
			{
				mast->r_arr_st[r]->c[0] = ft_atoi(tmp[1]);
				free(tmp[1]);
				mast->r_arr_st[r]->c[1] = ft_atoi(tmp[2]);
				free(tmp[2]);
			}
			else
				ERROR("invalid coordinates");
			free(tmp);
			r++;
		}
		else if (valid_link(mast) == 1)
			mast->link_arr[l++] = ft_strsplit(mast->file[mast->j], '-');
		mast->j++;
	}
	mast->r_arr_st[r] = 0;
	mast->link_arr[l] = 0;
}
