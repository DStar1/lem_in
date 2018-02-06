/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:10:34 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/05 18:36:58 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	send_ants(t_mast *mast)
{
	int i;
	int start_i;
	int j;
	int ants_sent;
	int ants[mast->ants];

	for (int q = 0; q < mast->ants; q++)
		ants[q] = -1;

	start_i = 1;
	ants_sent = 0;
	j = -mast->ants;
	while (j < mast->qsize)//ants[mast->ants - 1] < mast->qsize)//j < mast->qsize)
	{
		if (ants_sent < mast->ants)
			ants_sent++;
		i = 1;
		i = mast->qsize;
		while (i >= 1)//<= ants_sent && i <= mast->qsize)//(i <= ants_sent && i <= mast->qsize)// && i <= mast->ants) //(ants[mast->ants] < mast->qsize)
		{
			ants[i - 1] += 1;
			if (ants[i - 1] >= 0 && ants[i - 1] <= mast->qsize)
				printf("L%d-%s ", ants[i - 1] + 1, mast->r_arr_st[mast->path[i][0]]->room);
			// start_i++;
			i--;
		}
		// start_i = tmp;
		j++;
		// j = -1;
		// while (j < mast->qsize)
		// {
		// 	if (mast->path[j][3])
		// 		printf("L%d-%s", ants_sent, mast->r_arr_st[mast->path[j][0]]->room);
		// }
		printf("\n");
	}
}

void	free_linked_arr(t_mast *mast)
{
	int i;

	i = 0;
	while (i < mast->rooms)
	{
		while (mast->hash_arr[i] != 0)
		{
			// printf("(%d, %s)", mast->hash_arr[i]->p, mast->hash_arr[i]->l[0]);
			free(mast->hash_arr[i]);
			mast->hash_arr[i] = mast->hash_arr[i]->next;
			//j++;
		}
		// printf("\n");
		i++;
	}
	free(mast->hash_arr);
}

/*
** Find array size to malloc
*/

int		find_size(t_mast *mast)
{
	mast->y_len = 0;
	mast->fd = open(mast->filename, O_RDONLY);/////get rid of when reading from stdin
	// mast->fd = 0;
	while ((get_next_line(mast->fd, &mast->ln)))
	{
		if (ft_strncmp(mast->ln, "#", 1) != 0)
			mast->y_len++;
		else if (ft_strcmp(mast->ln, "##start") == 0 || ft_strcmp(mast->ln, "##end") == 0)
			mast->y_len++;
		
		free(mast->ln);
		mast->ln = NULL;
	}
	free(mast->ln);
	close(mast->fd);//get rid of when reading from stdin
	return (0);
}

int     main(int ac, char **av)
{
	t_mast mast;
	//t_links *links;

	//mast.fd = 0;
	//links = (t_links*)ft_memalloc(sizeof(t_links));
	ft_bzero(&mast, sizeof(mast));
	mast.filename = ft_strdup(av[1]);
	find_size(&mast);
	mast.fd = open(mast.filename, O_RDONLY);/////get rid of when reading from stdin
	// mast.fd = 0;
	mast.file = (char **)malloc(sizeof(char*) * (mast.y_len + 1));//maybe null terminate it
	mast.file[mast.y_len] = 0;
	parse(&mast);

	//mast.j = -1;
	// while (++mast.j < mast.y_len)
	// 	printf("!:%s\n", mast.file[mast.j]);
	make_arrs(&mast);


	set_links(&mast);

	solve(&mast);//solves
	

	send_ants(&mast);

	////ft_putarr(mast.file);
	close(mast.fd);//get rid of when reading from stdin
	printf("y_len: %d, ants: %d, rooms: %d, links: %d\n", mast.y_len, mast.ants, mast.rooms, mast.links);

	free_linked_arr(&mast);
	// while (1)
	// 	;
	//exit(1);
    return (0);
}

///segfaults if no rooms