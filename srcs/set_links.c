/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:15:22 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/29 20:27:46 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	go_thru_lnks(t_mast *mast)
{
	int i;
	t_links *tmp;

	i = 0;
	while (i < mast->rooms)
	{
		tmp = mast->hash_arr[i];
		while (tmp != 0)
		{
			printf("(%d, %s)", tmp->p, tmp->l[0]);
			//free(tmp);
			tmp = tmp->next;
		}
		printf("\n");
		i++;
	}
}

t_links	*build_links(t_mast *mast)
{
	t_links *list = NULL;
	t_links *begin = NULL;
	t_links *newlist;
	int i;
	
	i = 0;
	//list = 0;
	begin = list;
	while (i < 5)
	{
		newlist = (t_links*)malloc(sizeof(t_links));
		newlist->p = i;//the first time you need to set this to start
		newlist->l = mast->start_arr;
		newlist->next = 0;
		if (!begin)
		{
			newlist->l1 = mast->start_string;
			begin = newlist;
		}
		if (!list)
			list = newlist;
		else
		{
			list->next = newlist;
			list = newlist;
		}
		i++;
	}
	return (begin);	
}

int		set_links(t_mast *mast)
{
	int i;

	i = 0;
	mast->start_arr = ft_strsplit(mast->start_string, ' ');
	mast->hash_arr = (t_links**)ft_memalloc(sizeof(t_links*) * mast->rooms + 1);
	while (i < mast->rooms)
	{
		mast->hash_arr[i] = build_links(mast);
		i++;
	}
	mast->hash_arr[i] = 0;
	go_thru_lnks(mast);
	return (0);
}