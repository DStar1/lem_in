/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:10:34 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/09 14:46:42 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	print(t_mast *mst, int ants_sent, int ants_i, int i)
{
	if (ants_i >= 0 && ants_i < mst->qsize)
	{
		ft_putchar('L');
		ft_putnbr(i + 1);
		ft_putchar('-');
		ft_putstr(mst->r_arr_st[mst->path[ants_i]]->room);
		IF(i != ants_sent - 1, ft_putchar(' '));
	}
}

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
		(ants_sent < mst->ants) ? ants_sent++ : 0;
		i = -1;
		while (++i < ants_sent)
			BRACKETS(ants[i] += 1, print(mst, ants_sent, ants[i], i));
		if (mst->qsize > 2)
			ft_putchar('\n');
		else if (mst->qsize <= 2 && mst->path[ants[mst->ants - 1]] == mst->end)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

/*
** If start char is 'L' it is false
** ignore anything that starts with a # except start and end
*/

int			parse_char(t_mast *mst)
{
	mst->y_len = 0;
	while ((get_next_line(mst->fd, &mst->ln)))
	{
		if (ft_strcmp(mst->ln, "") == 0)
			break ;
		IF_ERROR(ft_strncmp(mst->ln, "L", 1) == 0, "L names are invalid\n");
		if (ft_strncmp(mst->ln, "#", 1) != 0 || !ft_strcmp(mst->ln, "##start")
			|| ft_strcmp(mst->ln, "##end") == 0)
			mst->y_len++;
		if (!mst->file_str)
			mst->file_str = ft_strdup(mst->ln);
		else
		{
			mst->new_str = ft_strjoin_clr_1st(mst->file_str, mst->ln);
			mst->file_str = mst->new_str;
		}
		mst->new_str = ft_strjoin_clr_1st(mst->file_str, "\n");
		mst->file_str = mst->new_str;
		ft_memdel((void**)&mst->ln);
	}
	IF_ERROR((mst->y_len == 0), "Empty\n");
	ft_memdel((void**)&mst->ln);
	return (0);
}

static void	put_int_2d_arr(t_mast *mst)
{
	int		q;
	int		y;
	int		p;
	char	*tmp;

	q = 0;
	y = 0;
	p = -1;
	mst->file = (char **)ft_memalloc(sizeof(char*) * (mst->y_len + 1));
	while (mst->file_str[++p])
		if (mst->file_str[p] == '\n')
		{
			tmp = ft_strsub(mst->file_str, q, p - q);
			if ((!ft_strcmp(tmp, "##start") || !ft_strcmp(tmp, "##end"))
			&& mst->file_str[p + 1] == '#')
				ERROR("Invalid start/end\n");
			if (ft_strncmp(tmp, "#", 1) != 0 || !ft_strcmp(tmp, "##start")
			|| ft_strcmp(tmp, "##end") == 0)
				mst->file[y++] = tmp;
			else
				ft_memdel((void**)&tmp);
			q = p + 1;
		}
}

int			main(int ac, char **av)
{
	t_mast	mst;

	if (ac != 1 || ft_strcmp(av[0], "./lem-in") != 0)
		ERROR("\nMust pipe file into stdin\nExample: ./lem-in < example.txt\n");
	ft_bzero(&mst, sizeof(mst));
	parse_char(&mst);
	put_int_2d_arr(&mst);
	parse(&mst);
	make_arrs(&mst);
	set_links(&mst);
	solve(&mst);
	ft_putstr(mst.file_str);
	ft_putchar('\n');
	send_ants(&mst);
	free_linked_arr(&mst);
	exit(1);
	return (0);
}
