/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:35:29 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 12:18:07 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// static void	go_thru_lnks(t_mast *mast)
// {
// 	int i;
// 	t_links *tmp;

// 	i = 0;
// 	while (i < mast->rooms)
// 	{
// 			if (i == mast->start)
// 				printf("START:\n");
// 			if (i == mast->end)
// 				printf("END:\n");
// 		printf("CC:(room:%s)(%d, %d) |", mast->r_arr_st[i]->room, mast->r_arr_st[i]->c[0], mast->r_arr_st[i]->c[1]);
// 		i++;
// 	}
// 	printf("\n\n");
// }

void	make_arrs(t_mast *mast)
{
	int r;
	int l;
	int i;
	char **tmp;

	r = 0;
	l = 0;
	mast->j = 0;
	//mast->room_arr = (char***)ft_memalloc(sizeof(char**) * mast->rooms + 1);
	mast->r_arr_st = (t_room**)ft_memalloc(sizeof(t_room*) * mast->rooms);
	mast->link_arr = (char***)ft_memalloc(sizeof(char**) * mast->links + 1);
	while (mast->file[mast->j])// <= mast->y_len)
	{
		if (valid_room(mast) == 1)
		{
			mast->r_arr_st[r] = (t_room*)ft_memalloc(sizeof(t_room));
			// mast->room_arr[r] = ft_strsplit(mast->file[mast->j], ' ');
			tmp = ft_strsplit(mast->file[mast->j], ' ');
			mast->r_arr_st[r]->room = tmp[0];
			//mast->r_arr_st[r]->visited = -1;
			if (ft_isnbr(tmp[1]) && ft_isnbr(tmp[2]))//change to numbers for the coordinates of the struct
			{
				mast->r_arr_st[r]->c[0] = ft_atoi(tmp[1]);
				free(tmp[1]);
				mast->r_arr_st[r]->c[1] = ft_atoi(tmp[2]);
				free(tmp[2]);
			}
			else
				ERROR("invalid coordinates");//exit(1); //invalid coordinates
			//printf("r:(%s, %s, %s) ", mast->room_arr[r][0], mast->room_arr[r][1], mast->room_arr[r][2]);////////////////////////////
			free(tmp);
			r++;
		}
		else if (valid_link(mast) == 1)
		{
			mast->link_arr[l] = ft_strsplit(mast->file[mast->j], '-');
			// printf("l:(%s, %s) ", mast->link_arr[l][0], mast->link_arr[l][1]);////////////////////////////
			l++;
		}
		// if (tmp)
		// 	free_array(tmp);
		// printf("String: %s\n", mast->file[mast->j]);
		mast->j++;
	}
	mast->r_arr_st[r] = 0;
	//mast->room_arr[r] = 0;
	mast->link_arr[l] = 0;
	// printf("\n");
	// go_thru_lnks(mast);
		// printf("y_len: %d, links up to now: %d, line: %d, mast->link_arr[4]: %s\n", mast->y_len, l, mast->j, mast->link_arr[3][0]);
}
