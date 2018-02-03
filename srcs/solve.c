/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/02 14:25:35 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int     solve(t_mast *m)
{
	int i;
	t_links *tmp;

	i = 0;
	while (/*list is not empty*/)
	{
		tmp = mast->hash_arr[i];
		while (tmp != 0)
		{
			//printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
			//free(tmp);
			tmp = tmp->next;
		}
		printf("\n");
		i++;
	}
    return (0);
}