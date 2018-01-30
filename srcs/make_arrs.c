/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:35:29 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/29 21:12:33 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	make_arrs(t_mast *mast)
{
	int r;
	int l;

	r = 0;
	l = 0;
	mast->j = 0;
	mast->room_arr = (char***)ft_memalloc(sizeof(char**) * mast->rooms + 1);
	mast->link_arr = (char***)ft_memalloc(sizeof(char**) * mast->links + 1);
	while (mast->j < mast->y_len)
	{
		if (valid_room(mast) == 1)
		{
			mast->room_arr[r] = ft_strsplit(mast->file[mast->j], ' ');
			if (r == mast->start)
				printf("START:");
			if (r == mast->end)
				printf("END:");
			printf("r:(%s, %s, %s) ", mast->room_arr[r][0], mast->room_arr[r][1], mast->room_arr[r][2]);////////////////////////////
			r++;
		}
		if (valid_link(mast) == 1)
		{
			mast->link_arr[l] = ft_strsplit(mast->file[mast->j], '-');
			printf("l:(%s, %s) ", mast->link_arr[l][0], mast->link_arr[l][1]);////////////////////////////
			l++;
		}
		mast->j++;
	}
	mast->room_arr[r] = 0;
	mast->link_arr[l] = 0;
	printf("\n");
}