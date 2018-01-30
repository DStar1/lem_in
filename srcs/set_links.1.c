/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:15:22 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/29 19:36:52 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_links	*build_links(t_links *hashes)
{
	t_links *list = NULL;
	t_links *begin = NULL;
	t_links *newlist;
	int i = 5;
	list = 0;
	begin = list;
	while (i > 0)
	{
		newlist = (t_links*)malloc(sizeof(t_links));
		newlist->p = i;
		newlist->next = 0;
		if (!begin)
			begin = newlist;
		if (!list)
			list = newlist;
		else
		{
			list->next = newlist;
			list = newlist;
		}
		i--;
	}
	return (begin);


	// t_links *begin;
	// t_links *tmp;
	// int i;

	// i = 0;
	// begin = 0;
	// tmp = 0;
	// hashes = 0;
	// begin = hashes;
	// hashes->l1 = mast->start_string;
	// hashes->l2 = mast->end_string;
	// hases->next = 0;
	// while (i < 3)
	// {
	// 	tmp = (t_links*)ft_memalloc(sizeof(t_links));
	// 	tmp->next = 0;
	// 	if (!hashes)
	// 	{
	// 		hashes->l1 = mast->start_string;
	// 		hashes->l2 = mast->end_string;
	// 	}
	// 	else
	// 	{
	// 		//function to find what link is next
	// 	}
	// 	if (!begin)
	// 		begin = hashes;
	// 	hases->next = 0;
	// 	hashes = hashes->next;
	// 	i++;
	// }
	// return (begin);	
}

int		set_links(t_mast *mast)
{
	int i;

	i = 0;
	mast->hash_arr = (t_links**)ft_memalloc(sizeof(t_links*) * mast->rooms + 1);
	while (i < mast->rooms)
	{
		// mast->hash_arr[i] = (t_links*)ft_memalloc(sizeof(t_links));
		// mast->hash_arr[i]->next = 0;
		mast->hash_arr[i] = build_links(mast->hash_arr[i]);
		i++;
	}
	i = 0;
	while (i < mast->rooms)
	{
		while (mast->hash_arr[i] != 0)
		{
			printf("%d, ", mast->hash_arr[i]->p);
			mast->hash_arr[i] = mast->hash_arr[i]->next;
			//j++;
		}
		printf("\n");
		// mast->hash_arr[i] = (t_links*)ft_memalloc(sizeof(t_links));
		// mast->hash_arr[i]->next = 0;
		
		// mast->hash_arr->data
		// mast->hash_arr[i] = build_links(mast->hash_arr[i]);
		i++;
	}

	return (0);
}