/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:02:46 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/09 12:28:07 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_p_atoi(char *str, int start)
{
	int start1;
	int nb;

	nb = 0;
	start1 = start;
	while (str[start] && ft_isdigit(str[start]))
	{
		nb += (str[start] - '0');
		nb *= 10;
		start++;
	}
	nb /= 10;
	if (str[start] == '\0')
		return (nb);
	return (0);
}
