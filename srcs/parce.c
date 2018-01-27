/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:06:46 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/26 18:11:15 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		f_atoi(t_mast *mast, int start)
{
	int start1;
	int nb;

	nb = 0;
	start1 = start;
	while (mast->file[0][start] && ft_isdigit(mast->ln[start]))
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

int     parce(t_mast *mast)
{
	while ((get_next_line(mast->fd, &mast->ln)))
	{
		mast->file[mast->j++] = mast->ln;
		//free(mast->ln);
		//mast->ln = NULL;
	}
	free(mast->ln);
	mast->j = 0;
	while (mast->j < mast->y_len)
	{
		if (mast->j == 0)
			mast->ants = f_atoi(mast, 0);
		if (ft_strcmp(mast->file[mast->j], "##start") == 0)
			mast->start = ft_strlen(mast->file[mast->j]);//check for next line and that should exist and save it as start if it does
		if (ft_strcmp(mast->file[mast->j], "##end") == 0)
			mast->end = ft_strlen(mast->file[mast->j]);//check for next line and that should exist and save it as end if it does
		//ignore anything that starts with a ##
		mast->j++;
	}


	return (0);
}
