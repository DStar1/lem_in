/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 23:34:21 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Possibility to find more paths using depth first
*/

/*
**void		DFS(t_mast *mast, int i)
**{
**	t_links *tmp;
**	int		j;
**
**	if (!mast->found)
**	{
**		ft_putstr(mast->r_arr_st[i]->room);
**		ft_putchar('-');
**	}
**	if (i == mast->end)
**	{
**		mast->found = 1;
**		return ;
**	}
**	tmp = mast->hash_arr[i];
**	mast->r_arr_st[i]->visited = 1;
**	while (tmp != NULL)
**	{
**		j = 0;
**		i = tmp->l2_id;
**		if (!mast->r_arr_st[i]->visited)
**			DFS(mast, i);
**		tmp = tmp->next;
**	}
**}
*/

/*
** Make array path
*/

static void	construct_arr(t_mast *mast)
{
	t_res	*tmp;
	int		q;

	tmp = 0;
	mast->qsize++;
	q = mast->qsize - 1;
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
** construct path
*/

void		construct(t_mast *mast)
{
	t_res	*final;
	int		i;

	mast->qsize = 0;
	mast->res = 0;
	final = (t_res*)ft_memalloc(sizeof(t_res));
	final->next = 0;
	while (1)
	{
		final->qu = (int*)mast->que[mast->weight];
		IF(!mast->res, mast->res = final);
		if (mast->que[mast->weight][0] == mast->start)
			break ;
		i = -1;
		while (++i <= mast->cnt)
			if (mast->que[i][0] == mast->que[mast->weight][1])
			{
				mast->weight = i;
				mast->qsize++;
				final->next = (t_res*)ft_memalloc(sizeof(t_res));
				final = final->next;
				break ;
			}
	}
	construct_arr(mast);
}

/*
** loop until you find the end
** mast->que[mast->rooms][3]
** (0 is name of current, 1 is name of next, 2 is mast->weight)
** mast->cnt is to keep track of where to add next room to mast->que
** go through list of all connected points
** checks if the next link is already in mast->que
** if no and it has less mast->weight,
** set the next mast->que to the current next node
** if we have reached the end, we have found the path
*/

static int	loop_list(t_mast *mast)
{
	while (mast->tmp != NULL)
	{
		mast->cnt1 = 0;
		mast->i = -1;
		while (++mast->i <= mast->cnt)
			if ((mast->que[mast->i][0] == mast->tmp->l2_id) &&
			mast->que[mast->i][2] != 0 && mast->que[mast->i][2] <= mast->weight)
				mast->cnt1++;
		if (mast->cnt1 == 0)
		{
			mast->que[mast->cnt][0] = mast->tmp->l2_id;
			mast->que[mast->cnt][1] = mast->tmp->l1_id;
			mast->que[mast->cnt][2] = mast->weight;
			if (mast->que[mast->cnt][0] == mast->end)
			{
				mast->weight = mast->cnt;
				construct(mast);
				return (1);
			}
			mast->cnt++;
		}
		mast->tmp = mast->tmp->next;
	}
	return (0);
}

void		dkstra(t_mast *mast)
{
	while (mast->que[mast->weight][0] != mast->end)
	{
		mast->tmp = mast->hash_arr[mast->que[mast->weight][0]];
		(mast->cnt == 0) ? mast->cnt++ : 0;
		mast->weight++;
		if (mast->weight >= mast->rooms)
			ERROR("There's no path\n");
		if (loop_list(mast) == 1)
			return ;
	}
}

int			solve(t_mast *mast)
{
	int o;

	mast->que = (int**)ft_memalloc(sizeof(int*) * mast->rooms);
	o = -1;
	while (++o < mast->rooms)
	{
		mast->que[o] = (int*)ft_memalloc(sizeof(int) * 3);
		mast->que[o][0] = -1;
		mast->que[o][1] = -1;
	}
	mast->que[0][0] = mast->start;
	mast->que[0][2] = 1;
	mast->r_arr_st[mast->que[0][0]]->weight = 0;
	dkstra(mast);
	return (0);
}
