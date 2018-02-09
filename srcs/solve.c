/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 20:47:20 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Possibility to find more paths using depth first
*/

void	DFS(t_mast *mast, int i)
{
	t_links *tmp;
	int j;
   
	
	if (!mast->found)
		printf("%s-",mast->r_arr_st[i]->room);
	if (i == mast->end)
	{
		mast->found = 1;
		return ;
	}
	tmp = mast->hash_arr[i];
	mast->r_arr_st[i]->visited = 1;
	while(tmp!=NULL)//
	{
		j = 0;
	   i=tmp->l2_id;

	   if(!mast->r_arr_st[i]->visited)
			DFS(mast, i);
		tmp=tmp->next;
	}
}

/*
** construct path
*/

void 	construct(t_mast *mast)
{
	int weight = mast->weight;
	int cnt = mast->cnt;
	t_res *final;
	t_res *tmp = 0;
	//int	final[cnt][3];
	
	mast->qsize = 0;
	mast->res = 0;
	final = (t_res*)ft_memalloc(sizeof(t_res));
	final->next = 0;
	while (1)
	{
		final->qu = (int*)mast->que[weight];
		final->ants = 0;
		if (!mast->res)
			mast->res = final;
		if (mast->que[weight][0] == mast->start)
			break ;
		for (int i = 0; i <= cnt; i++)
		{
			if (mast->que[i][0] == mast->que[weight][1])
			{
				weight = i;
				mast->qsize++;
				final->next = (t_res*)ft_memalloc(sizeof(t_res));
				final = final->next;
				break ;
			}
		}
	}
	final = 0;
	mast->qsize++;
	int q = mast->qsize - 1;
	mast->path = (int*)ft_memalloc(sizeof(int) * mast->qsize);
	while (mast->res)
	{
		mast->path[q] = mast->res->qu[0];
		q--;
		tmp = mast->res;
		mast->res = mast->res->next;
		free(tmp);
	}
}

/*
** loop until you find the end
** mast->que[mast->rooms][3] (0 is name of current, 1 is name of next, 2 is weight)
*/

void 	dkstra(t_mast *mast)
{
	t_links *tmp;
	int last;
	int weight;
	int cnt;
	int cnt1;

	weight = 0;
	last = 0;
	cnt = 0;
	cnt1 = 0;
	mast->que = (int**)ft_memalloc(sizeof(int*) * mast->rooms);
	for (int o = 0; o < mast->rooms; o++)
	{
		mast->que[o] = (int*)ft_memalloc(sizeof(int) * 3);
		mast->que[o][0] = -1;
		mast->que[o][1] = -1;
	}
	mast->que[0][0] = mast->start;
	mast->que[0][2] = 1;//added one to get rid of error
	mast->r_arr_st[mast->que[0][0]]->weight = weight;
	while (mast->que[weight][0] != mast->end)// && weight < mast->rooms) //
	{
		tmp = mast->hash_arr[mast->que[weight][0]];
		(cnt == 0) ? cnt++ : 0; //keep track of where to add next room to mast->que
		weight++;
		if (weight >= mast->rooms)
			ERROR("There's no path\n");
		while(tmp != NULL)//go through list of all connected points
		{
			cnt1 = 0;
			int i = 0;
			for (i = 0; i <= cnt && i < mast->rooms; i++)//go through the mast->queue up to the last one set
				if ((mast->que[i][0] == tmp->l2_id) && mast->que[i][2] != 0 && mast->que[i][2] <= weight)//checks if the next link is already in mast->que// exists and it has less weight than the current weight and it is one of the next links, cnt1++
					cnt1++;
			if (cnt1 == 0) //if non of the above was true, set the next mast->que to the current next node
			{
				mast->que[cnt][0] = tmp->l2_id;
				mast->que[cnt][1] = tmp->l1_id;
				mast->que[cnt][2] = weight;				
				if ((int)mast->que[cnt][0] == mast->end) //if we have reached the end, we have found the path
				{
					mast->weight = cnt;
					mast->cnt = cnt;
					construct(mast);
					return ;
				}
				cnt++;
			}
			tmp = tmp->next;
		}
	}
}

int     solve(t_mast *mast)
{
	dkstra(mast);
	return (0);
}



