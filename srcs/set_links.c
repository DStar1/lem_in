/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:15:22 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/09 01:27:08 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Free array of linked lists
*/

void		free_linked_arr(t_mast *mst)
{
	int		i;
	t_links *tmp;

	i = 0;
	while (i < mst->rooms)
	{
		while (mst->hash_arr[i] != 0)
		{
			tmp = mst->hash_arr[i];
			mst->hash_arr[i] = mst->hash_arr[i]->next;
			free(tmp);
		}
		i++;
	}
	free(mst->hash_arr);
}

/*
** compare name with first or second link
*/

int			find_next_lnk(t_mast *mast, t_links *newlist, int boolean)
{
	if (!ft_strcmp(mast->r_arr_st[mast->i]->room, mast->link_arr[mast->j][0]))
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
	if (!ft_strcmp(mast->r_arr_st[mast->i]->room, mast->link_arr[mast->j][1]))
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

static void	links(t_mast *mast,
					t_links **list,
					t_links **begin,
					t_links **newlist)
{
	int i;

	*newlist = (t_links*)ft_memalloc(sizeof(t_links));
	find_next_lnk(mast, *newlist, 1);
	(*newlist)->l1_id = mast->i;
	i = -1;
	while (++i < mast->rooms)
		if (ft_strcmp((*newlist)->l2, mast->r_arr_st[i]->room) == 0)
		{
			(*newlist)->l2_id = i;
			break ;
		}
	if (!*begin)
		*begin = *newlist;
	if (!*list)
		*list = *newlist;
	else
	{
		(*list)->next = *newlist;
		*list = *newlist;
	}
}

t_links		*build_links(t_mast *mast)
{
	t_links *list;
	t_links *begin;
	t_links *newlist;

	mast->j = 0;
	list = NULL;
	begin = list;
	while (mast->j < mast->links)
	{
		if (find_next_lnk(mast, newlist, 0) == 1)
		{
			links(mast, &list, &begin, &newlist);
		}
		mast->j++;
	}
	return (begin);
}

/*
** Builds hash table for searching for next points
** array of linked lists
*/

int			set_links(t_mast *mast)
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
