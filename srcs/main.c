/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:10:34 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 20:50:26 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	send_ants(t_mast *mast)
{
	int i;
	int start_i;
	int j;
	int ants_sent;
	int ants[mast->ants];////////////////careful with static memory

	// ants = (int*)ft_memalloc(sizeof(int) * mast->ants);
	for (int q = 0; q < mast->ants; q++)
		ants[q] = 0;
	ants_sent = 0;
	while (mast->path[ants[mast->ants - 1]] != mast->end)
	{
		if (ants_sent < mast->ants)
			ants_sent++;
		i = 0;
		while (i < ants_sent)
		{
			ants[i] += 1;
			if (ants[i] >= 0 && ants[i] < mast->qsize)
			{
				ft_putchar('L');
				ft_putnbr(i + 1);
				ft_putchar('-');
				ft_putstr(mast->r_arr_st[mast->path[ants[i]]]->room);
				if (i != ants_sent - 1)
					ft_putchar(' ');
			}
			i++;
		}
		if (mast->qsize > 2)
			ft_putchar('\n');
		else if (mast->qsize <= 2 && mast->path[ants[mast->ants - 1]] == mast->end)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

void	free_linked_arr(t_mast *mast)
{
	int i;
	t_links *tmp;

	i = 0;
	while (i < mast->rooms)
	{
		while (mast->hash_arr[i] != 0)
		{
			// printf("(%d, %s)", mast->hash_arr[i]->p, mast->hash_arr[i]->l[0]);
			tmp = mast->hash_arr[i];
			mast->hash_arr[i] = mast->hash_arr[i]->next;
			free(tmp);
		}
		i++;
	}
	free(mast->hash_arr);
}

/*
** Maybe handle ##coments in intial parcing with getnext line. just dont add the comments into mast->file
** also maybe if start char is 'L' it is false
** ignore anything that starts with a ##
*/

int		parse_char(t_mast *mast) //sometimes it gives an error beacuse I chaged this
{
	char *new;
	char *tmp;
	char last;

	mast->y_len = 0;
	// mast->fd = open(mast->filename, O_RDONLY);/////get rid of when reading from stdin
	// mast->ln = NULL;
	// mast->fd = 0;
	while ((get_next_line(mast->fd, &mast->ln)))
	{
		if (ft_strcmp(mast->ln, "") == 0) //need a way to get out of the loop
			break ;
		// printf("%d\n", mast->y_len);
		if (ft_strncmp(mast->ln, "L", 1) == 0)
			ERROR("L names are invalid\n");
		if (ft_strncmp(mast->ln, "#", 1) != 0 || ft_strcmp(mast->ln, "##start") == 0 || ft_strcmp(mast->ln, "##end") == 0)
		{
			if (!mast->file_str)
				mast->file_str = ft_strdup(mast->ln);
			else
			{
				new = ft_strjoin_clr_1st(mast->file_str, mast->ln);
				mast->file_str = new;
			}
			new = ft_strjoin_clr_1st(mast->file_str, "\n");
			mast->file_str = new;
			mast->y_len++;
		}
		free(mast->ln);
		mast->ln = NULL;
	}
	if (mast->y_len == 0)
		ERROR("Empty\n");
	free(mast->ln);
	mast->ln = NULL;
	// close(mast->fd);//get rid of when reading from stdin
	return (0);
}

int     main(int ac, char **av)
{
	t_mast mast;
	int q;
	int y;
	// mast.filename = ft_strdup(av[1]);
	if (ac != 1 || ft_strcmp(av[0], "./lem-in") != 0)
	 	ERROR("\nMust pipe file into stdin\nExample: ./lem-in < example.txt\n");
	ft_bzero(&mast, sizeof(mast));
	parse_char(&mast);
	mast.file = (char **)ft_memalloc(sizeof(char*) * (mast.y_len + 1));//maybe null terminate it
	mast.file[mast.y_len] = 0;
	q = 0;
	y = 0;
	// printf("%d\n", mast.y_len);
	for (int p = 0; mast.file_str[p]; p++)
	{	
		if (mast.file_str[p] == '\n')
		{
			mast.file[y++] = ft_strsub(mast.file_str, q, p - q);
			q = p + 1;
		}
	}
	parse(&mast);
	make_arrs(&mast);
	set_links(&mast);
	solve(&mast);
	ft_putstr(mast.file_str);
	ft_putchar('\n');
	send_ants(&mast);
	free_linked_arr(&mast);
	// while (1)
	// 	;
	exit(1);
    return (0);
}

///segfaults if no rooms
