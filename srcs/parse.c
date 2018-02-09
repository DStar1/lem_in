/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:06:46 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 17:14:48 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		f_atoi(t_mast *mast, int start)
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
	if (mast->file[0][start] == '\0') //checks to see how many ants there are
		return (nb);
	return (0);
}

/*
** Checks to see if it's a valid link
*/

int		valid_link(t_mast *mast)
{
	//if room has 3 things and no spaces in the begining and end and in the 2
	//last things are numbers the first can be a string
	char *str;

	str = mast->file[mast->j];
	if (str)
	{
		if (str[0] != ' ' && str[ft_strlen(str) - 1] != ' ')
		{
			if (ft_cntstrwords(str, '-') == 2)//maybe instead, check to see if there is only one '-' and two variables because right now there can be multiple '---' or if there is "0- 0"
			{
				//printf("link is correct");
				return (1);
			}
		}
		else
			ERROR("Invalid links\n");//exit (1);/////////////
	}
	// exit (1);/////////////
	// if (str)
	// 	free(str);
	return (0);
}

/*
** Checks to see if it's a valid room
*/

int		valid_room(t_mast *mast)
{
	//if room has 3 things and no spaces in the begining and end and in the 2
	// last things are numbers the first can be a string
	char *str;

	str = mast->file[mast->j];
	if (str)
	{
		if (str[0] != ' ' && str[ft_strlen(str) - 1] != ' ')
		{
			if (ft_cntstrwords(str, ' ') == 3)
			{
				//printf("start is correct");
				return (1);
			}
		}
		else
			ERROR("Invalid rooms\n");//exit (1);/////////////
	}
	// exit (1);/////////////
	// if (str)
	// 	free(str);
	return (0);
}

/*
** Maybe handle ##coments in intial parcing with getnext line. just dont add the comments into mast->file
** also maybe if start char is 'L' it is false
*/

int     parse(t_mast *mast)
{
	mast->j = -1;
	while (++mast->j < mast->y_len) //reads file and validation
	{
		// printf("%s\n", mast->file[mast->j]);
		if (mast->j == 0 && ft_isnbr(mast->file[mast->j]))
			mast->ants = f_atoi(mast, 0);
		if (mast->j == 0 && mast->ants == 0)
			ERROR("No ants\n");
		if (valid_room(mast) && valid_link(mast))
			ERROR("Illegal name\n");
		if (valid_room(mast))
			mast->rooms++;
		if (valid_link(mast))
			mast->links++;
		if (ft_strcmp(mast->file[mast->j], "##start") == 0 && mast->file[mast->j + 1])
		{
			mast->j++;
			if (valid_room(mast) != 0)
			{
				if (mast->start_string)
					ERROR("Multiple starts\n");
				mast->start_string = mast->file[mast->j];
				mast->start = mast->rooms;
				mast->rooms++;
			}
			else
				ERROR("Invalid start\n");//exit (1);/////////////
		}
		else if (ft_strcmp(mast->file[mast->j], "##end") == 0 && mast->file[mast->j + 1])
		{
			mast->j++;
			// printf("YOUR IN %d\n", mast->rooms);
			if (valid_room(mast) != 0)
			{
				if (mast->end_string)
					ERROR("Multiple ends\n");
				mast->end_string = mast->file[mast->j];
				mast->end = mast->rooms;
				mast->rooms++;
			}
			else
				ERROR("Invalid start\n");//exit (1);/////////////
		}
		else if (!valid_room(mast) && !valid_link(mast) && mast->j != 0)
			ERROR("Invalid room/link\n");
		//ignore anything that starts with a ##
		// mast->j++;
	}
	if (mast->rooms == 0)
		ERROR("No rooms\n");//exit (1);
	if (mast->links == 0)
		ERROR("No links\n");//exit (1);
	if (!mast->start_string)
		ERROR("No start\n");//exit (1);
	if (!mast->end_string)
		ERROR("No end\n");//exit (1);
	return (0);
}
