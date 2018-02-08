/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/07 20:39:23 by hasmith          ###   ########.fr       */
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
// 		tmp = mast->hash_arr[i];
// 		while (tmp != 0)
// 		{
// 			printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
// 			//free(tmp);
// 			tmp = tmp->next;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

void DFS(t_mast *mast, int i)
{
	t_links *tmp;
	int j;
   
	
	if (!mast->found)
		printf("%s-",mast->r_arr_st[i]->room);
	if (i == mast->end)
		{mast->found = 1;return ;}
	// if (i == mast->start)
	//     printf("Start: ");
	// if (i == mast->end)
	//     {printf("End: ");return ;}
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

//////////////


void construct(t_mast *mast)
{
	int weight = mast->weight;
	int **que = mast->que;
	int cnt = mast->cnt;
	///////construct path
	mast->qsize = 0;
	//int	final[cnt][3];
	mast->res = 0;
	t_res *final = 0;
	final = (t_res*)malloc(sizeof(t_res));
	final->next = 0;
	while (1)
	{
		final->qu = (int*)que[weight];
		final->ants = 0;
		if (!mast->res)
			mast->res = final;
		// printf("(q:%d)%s-", mast->qsize, mast->r_arr_st[que[weight][0]]->room);
		// final[q][0] = que[weight][0];
		// final[q--][1] = que[weight][1];
		if (que[weight][0] == mast->start)
			break ;
		for (int i = 0; i <= cnt; i++)
		{
			if (que[i][0] == que[weight][1])
			{
				weight = i;
				mast->qsize++;
				final->next = (t_res*)malloc(sizeof(t_res));
				final = final->next;
				break ;
			}
		}
	}
	final = 0;
	mast->qsize++;
	int q = mast->qsize - 1;
	//int **path;//[mast->qsize + 1];
	mast->path = (int*)malloc(sizeof(int) * mast->qsize);
	// printf("qsize: %d\n", mast->qsize);
	while (mast->res)
	{
		// printf("\nQ:%d, %s-", q, mast->r_arr_st[mast->res->que[0]]->room);
		mast->path[q] = mast->res->qu[0];
		//printf("\nnew: Q:%d", mast->path[q]);
		q--;
		mast->res = mast->res->next;
	}
}

///

void dkstra(t_mast *mast)
{
	t_links *tmp;
	int	**que;//[mast->rooms][3]; //0 is name of current, 1 is name of next, 2 is weight
	int last;
	int weight;
	int cnt;
int w = 0;////////////
	weight = 0;
	last = 0;
	cnt = 0;
	int cnt1 = 0;
	que = (int**)ft_memalloc(sizeof(int*) * mast->rooms);
	for (int o = 0; o < mast->rooms; o++)
	{
		que[o] = (int*)ft_memalloc(sizeof(int) * 3);
		que[o][0] = -1;
		que[o][1] = -1;
		// que[o][2] = -1;
	}
	que[0][0] = mast->start;
	que[0][2] = 1;//added one to get rid of error
	mast->r_arr_st[que[0][0]]->weight = weight;
	while (que[weight][0] != mast->end)// && weight < mast->rooms) //loop until you find the end
	{
		
			// printf("%s\n", mast->r_arr_st[que[weight][0]]->room);
		tmp = mast->hash_arr[que[weight][0]];
		(cnt == 0) ? cnt++ : 0; //keep track of where to add next room to que
		//if cnt is == mast->rooms, there is no path?
		weight++;
		//cnt = weight;
		//que[weight] = (int*)ft_memalloc(sizeof(int) * 3);
		while(tmp != NULL)//go through list of all connected points
		{
			cnt1 = 0;
			int i = 0;
			for (i = 0; i <= cnt && i < mast->rooms; i++)//go through the queue up to the last one set
			{
				// if (que[i][0] == que[cnt - 1][0])// || que[i][0] == que[cnt][1])
				// 	cnt1++;
				if ((que[i][0] == tmp->l2_id) && que[i][2] != 0 && que[i][2] <= weight)//checks if the next link is already in que// exists and it has less weight than the current weight and it is one of the next links, cnt1++
					cnt1++;
			}
			if (cnt1 == 0) //if non of the above was true, set the next que to the current next node
			{
				que[cnt][0] = tmp->l2_id;
				que[cnt][1] = tmp->l1_id;
				que[cnt][2] = weight;
				// printf("%s-%s;wieght:%d\n", mast->r_arr_st[que[cnt][0]]->room, mast->r_arr_st[que[cnt][1]]->room, weight);
				
				if ((int)que[cnt][0] == mast->end) //if we have reached the end, we have found the path
				{
					// printf("weight: %d, l: %d, %d, \n", weight, cnt, que[cnt][0]);
					mast->weight = cnt;
					mast->que = que;
					mast->cnt = cnt;
					construct(mast);
					return ;
				}
				cnt++;
			}

			//mast->r_arr_st[que[cnt][0]]->weight = weight;
			//if(!mast->r_arr_st[i]->visited)

			tmp = tmp->next;
			// w++;
		}
		// printf("que[weight][0]: %d\n", que[weight][0]);
		// for (int l = 0; l < weight; l++)
		// 	if (que[l][0] == mast->end)
		// 		printf("weight: %d, l: %d, %d, ", weight, l, que[l][0]);
		// if (que[weight][0] == mast->end)// || que[cnt-1][0] == mast->end)
		// {
		// 	ft_putnbr(1);
		// 	break ;
		// }
		//w++;
	}
}










int     solve(t_mast *mast)
{
	// printf("\n", mast->start);
	dkstra(mast);
	//DFS(mast, mast->start);
	// printf("\n");

	
	// int i;
	// t_links *tmp;

	// i = 0;
	// while (/*list is not empty*/)
	// {
	// 	tmp = mast->hash_arr[i];
	// 	while (tmp != 0)
	// 	{
	// 		//printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
	// 		//free(tmp);
	// 		tmp = tmp->next;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	return (0);
}



