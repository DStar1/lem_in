/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:10:34 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/09 00:11:03 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		send_ants(t_mast *mst)
{
	int i;
	int start_i;
	int ants_sent;
	int ants[mst->ants];
	int q;

	q = -1;
	while (++q < mst->ants)
		ants[q] = 0;
	ants_sent = 0;
	while (mst->path[ants[mst->ants - 1]] != mst->end)
	{
		if (ants_sent < mst->ants)
			ants_sent++;
		i = -1;
		while (++i < ants_sent)
		{
			ants[i] += 1;
			if (ants[i] >= 0 && ants[i] < mst->qsize)
			{
				ft_putchar('L');
				ft_putnbr(i + 1);
				ft_putchar('-');
				ft_putstr(mst->r_arr_st[mst->path[ants[i]]]->room);
				if (i != ants_sent - 1)
					ft_putchar(' ');
			}
		}
		if (mst->qsize > 2)
			ft_putchar('\n');
		else if (mst->qsize <= 2 && mst->path[ants[mst->ants - 1]] == mst->end)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

void		free_linked_arr(t_mast *mst)
{
	int		i;
	t_links *tmp;

	i = 0;
	while (i < mst->rooms)
	{
		while (mst->hash_arr[i] != 0)
		{
			tmp = mst->hash_arr[i];
			mst->hash_arr[i] = mst->hash_arr[i]->next;
			free(tmp);
		}
		i++;
	}
	free(mst->hash_arr);
}

/*
** If start char is 'L' it is false
** ignore anything that starts with a # except start and end
*/

int			parse_char(t_mast *mst)
{
	char *new;

	mst->y_len = 0;
	while ((get_next_line(mst->fd, &mst->ln)))
	{
		if (ft_strcmp(mst->ln, "") == 0)
			break ;
		IF_ERROR(ft_strncmp(mst->ln, "L", 1) == 0, "L names are invalid\n");
		if (ft_strncmp(mst->ln, "#", 1) != 0 || !ft_strcmp(mst->ln, "##start")
			|| ft_strcmp(mst->ln, "##end") == 0)
		{
			if (!mst->file_str)
				mst->file_str = ft_strdup(mst->ln);
			else
			{
				new = ft_strjoin_clr_1st(mst->file_str, mst->ln);
				mst->file_str = new;
			}
			new = ft_strjoin_clr_1st(mst->file_str, "\n");
			mst->file_str = new;
			mst->y_len++;
		}
		ft_memdel((void**)&mst->ln);
	}
	IF_ERROR((mst->y_len == 0), "Empty\n");
	ft_memdel((void**)&mst->ln);
	return (0);
}

int			main(int ac, char **av)
{
	t_mast	mst;
	int		q;
	int		y;
	int		p;

	if (ac != 1 || ft_strcmp(av[0], "./lem-in") != 0)
		ERROR("\nMust pipe file into stdin\nExample: ./lem-in < example.txt\n");
	ft_bzero(&mst, sizeof(mst));
	parse_char(&mst);
	mst.file = (char **)ft_memalloc(sizeof(char*) * (mst.y_len + 1));
	mst.file[mst.y_len] = 0;
	q = 0;
	y = 0;
	p = -1;
	while (mst.file_str[++p])
		if (mst.file_str[p] == '\n')
		{
			mst.file[y++] = ft_strsub(mst.file_str, q, p - q);
			q = p + 1;
		}
	parse(&mst);
	make_arrs(&mst);
	set_links(&mst);
	solve(&mst);
	ft_putstr(mst.file_str);
	ft_putchar('\n');
	send_ants(&mst);
	free_linked_arr(&mst);
	while (1)
		;
	exit(1);
	return (0);
}
