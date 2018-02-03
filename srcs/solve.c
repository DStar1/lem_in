/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/02 19:33:25 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	go_thru_lnks(t_mast *mast)
{
	int i;
	t_links *tmp;

	i = 0;
	while (i < mast->rooms)
	{
		tmp = mast->hash_arr[i];
		while (tmp != 0)
		{
			printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
			//free(tmp);
			tmp = tmp->next;
		}
		printf("\n");
		i++;
	}
}

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

int     solve(t_mast *mast)
{

    printf("\n", mast->start);
    DFS(mast, mast->start);
    printf("\n");
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

