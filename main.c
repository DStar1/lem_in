/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:10:34 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/26 18:09:40 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Find array size to malloc
*/

int		find_size(t_mast *mast)
{
	mast->y_len = 0;
	mast->fd = open(mast->filename, O_RDONLY);/////get rid of when reading from stdin
	while ((get_next_line(mast->fd, &mast->ln)))
	{
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

	//mast.fd = 0;
	ft_bzero(&mast, sizeof(mast));
	mast.filename = av[1];
	find_size(&mast);
	mast.fd = open(mast.filename, O_RDONLY);/////get rid of when reading from stdin
	mast.file = (char **)malloc(sizeof(char*) * mast.y_len + 1);//maybe null terminate it
	mast.file[mast.y_len] = 0;
	parce(&mast);
	//ft_putarr(mast.file);
	close(mast.fd);//get rid of when reading from stdin
	printf("y_len: %d, ants: %d, start: %d, end: %d\n", mast.y_len, mast.ants, mast.start, mast.end);
    return (0);
}
