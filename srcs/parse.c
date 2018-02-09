/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:06:46 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 23:34:00 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Ants number
*/

int			f_atoi(t_mast *mast, int start)
{
	int start1;
	int nb;

	nb = 0;
	start1 = start;
	while (mast->file[0][start] && ft_isdigit(mast->file[0][start]))
	{
		nb += (mast->file[0][start] - '0');
		nb *= 10;
		start++;
	}
	nb /= 10;
	if (mast->file[0][start] == '\0')
		return (nb);
	return (0);
}

/*
** Checks to see if it's a valid link
** maybe instead, check to see if there is only one '-' and two variables
** because right now there can be multiple '---' or if there is "0- 0"
*/

int			valid_link(t_mast *mast)
{
	char *str;

	str = mast->file[mast->j];
	if (str)
	{
		if (str[0] != ' ' && str[ft_strlen(str) - 1] != ' ')
		{
			if (ft_cntstrwords(str, '-') == 2)
				return (1);
		}
		else
			ERROR("Invalid links\n");
	}
	return (0);
}

/*
** Checks to see if it's a valid room
** if room has 3 things and no spaces in the begining and end and in the 2
** last things are numbers the first can be a string
*/

int			valid_room(t_mast *mast)
{
	char *str;

	str = mast->file[mast->j];
	if (str)
	{
		if (str[0] != ' ' && str[ft_strlen(str) - 1] != ' ')
		{
			if (ft_cntstrwords(str, ' ') == 3)
				return (1);
		}
		else
			ERROR("Invalid rooms\n");
	}
	return (0);
}

static void	check_start_end(t_mast *mast)
{
	mast->j++;
	if (valid_room(mast) != 0)
		if (mast->start == -1)
		{
			if (mast->start_string)
				ERROR("Multiple starts\n");
			mast->start_string = mast->file[mast->j];
			mast->start = mast->rooms;
			mast->rooms++;
		}
		else
		{
			if (mast->end_string)
				ERROR("Multiple ends\n");
			mast->end_string = mast->file[mast->j];
			mast->end = mast->rooms;
			mast->rooms++;
		}
	else
		ERROR("Invalid start/end\n");
}

/*
** parce and validate from 2d file array
*/

int			parse(t_mast *mast)
{
	mast->j = -1;
	while (++mast->j < mast->y_len)
	{
		if (mast->j == 0 && ft_isnbr(mast->file[mast->j]))
			mast->ants = f_atoi(mast, 0);
		IF_ERROR((mast->j == 0 && mast->ants == 0), "Invalid ants\n");
		IF_ERROR((valid_room(mast) && valid_link(mast)), "Illegal name\n");
		if (valid_room(mast))
			mast->rooms++;
		if (valid_link(mast))
			mast->links++;
		if (!ft_strcmp(mast->file[mast->j], "##start"))
			mast->start = -1;
		if ((mast->start == -1 || (!ft_strcmp(mast->file[mast->j], "##end")))
			&& mast->file[mast->j + 1])
			check_start_end(mast);
		else if (!valid_room(mast) && !valid_link(mast) && mast->j != 0)
			ERROR("Invalid room/link\n");
	}
	IF_ERROR(mast->rooms == 0, "No rooms\n");
	IF_ERROR((mast->links == 0), "No links\n");
	IF_ERROR((!mast->start_string), "No start\n");
	IF_ERROR((!mast->end_string), "No end\n");
	return (0);
}
