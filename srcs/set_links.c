/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:15:22 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 20:38:45 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** compare name with first or second link
*/

int	find_next_lnk(t_mast *mast, t_links *newlist, int boolean)
{
	if (ft_strcmp(mast->r_arr_st[mast->i]->room, mast->link_arr[mast->j][0]) == 0)
	{
		if (boolean == 1)
		{
			newlist->l1 = mast->link_arr[mast->j][0];
			newlist->l2 = mast->link_arr[mast->j][1];
			newlist->start = mast->start;
			newlist->end = mast->end;
		}
		return (1);
	}
	else if (ft_strcmp(mast->r_arr_st[mast->i]->room, mast->link_arr[mast->j][1]) == 0)
	{
		if (boolean == 1)
		{
			newlist->l1 = mast->link_arr[mast->j][1];
			newlist->l2 = mast->link_arr[mast->j][0];
			newlist->start = mast->start;
			newlist->end = mast->end;
		}
		return (1);
	}
	return (0);
}

t_links	*build_links(t_mast *mast)
{
	t_links *list = NULL;
	t_links *begin = NULL;
	t_links *newlist;
	int i;
	
	mast->j = 0;
	// list = 0;
	begin = list;
	while (mast->j < mast->links)
	{
		if (find_next_lnk(mast, newlist, 0) == 1)
		{
			newlist = (t_links*)ft_memalloc(sizeof(t_links));
			find_next_lnk(mast, newlist, 1);
			newlist->l1_id = mast->i;//the first time you need to set this to start
			i = -1;
			while (++i < mast->rooms)
				if (ft_strcmp(newlist->l2, mast->r_arr_st[i]->room) == 0)
				{
					newlist->l2_id = i;
					break ;
				}
			if (!begin)
				begin = newlist;
			if (!list)
				list = newlist;
			else
			{
				list->next = newlist;
				list = newlist;
			}
		}
		mast->j++;
	}
	// if (!begin)
	// {
	// 	newlist = (t_links*)ft_memalloc(sizeof(t_links));
	// 	begin = newlist;
	// 	begin = 0;
	// }
	return (begin);	
}

/*
** Builds hash table for searching for next points
** array of linked lists
*/

int		set_links(t_mast *mast)
{
	mast->i = 0;
	mast->start_arr = ft_strsplit(mast->start_string, ' ');
	mast->hash_arr = (t_links**)ft_memalloc(sizeof(t_links*) * mast->rooms + 1);
	while (mast->i < mast->rooms)
	{
		mast->hash_arr[mast->i] = build_links(mast);
		mast->i++;
	}
	mast->hash_arr[mast->i] = 0;
	return (0);
}